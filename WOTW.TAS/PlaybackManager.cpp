#include "stdafx.h"
#include "PlaybackManager.h"


// This is set in NativeInjectionEntryPoint, we need access to it because DoPlayback formats the playback state string.
fnSeinCharacter_GetPosition SeinCharacter_GetPosition = (fnSeinCharacter_GetPosition)(0x0);
fnSeinCharacter_SetPosition SeinCharacter_SetPosition = (fnSeinCharacter_SetPosition)(0x0);
fnSeinCharacter_GetLocalSpeed SeinCharacter_GetLocalSpeed = (fnSeinCharacter_GetLocalSpeed)(0x0);
fnCharPlatformMovement_GetRigidbodyVelocity CharPlatformMovement_GetRigidbodyVelocity = (fnCharPlatformMovement_GetRigidbodyVelocity)(0x0);

// Can't do these three, do it in constructor.
fnUnityEngine_SetTimeScale UnityEngine_SetTimeScale = (fnUnityEngine_SetTimeScale)(0x0);
fnUnityEngine_SetVSyncCount UnityEngine_SetVSyncCount = (fnUnityEngine_SetVSyncCount)(0x0);
fnUnityEngine_SetMaximumDeltaTime UnityEngine_SetMaximumDeltaTime = (fnUnityEngine_SetMaximumDeltaTime)(0x0);
bool g_bPaused = false;
bool g_bPressedFrameStepThisFrame = false;
PlaybackManager * g_pPlaybackManager = nullptr;
unsigned long long g_qwPlayerInputInstance = 0x00000000;

InputButtonProcessor * g_pDash, *g_pJump, *g_pGrab, *g_pGlide, *g_pAbility1, *g_pAbility2, *g_pAbility3, *g_pButtonA, *g_pMenuSelect, *g_pAbilityWheel, *g_pBurrow, *g_pBash,
*g_pGrapple, *g_pPause, *g_pMenuClose, *g_pButtonB, *g_pButtonY, *g_pButtonX;
Core_Input * g_pCoreInput = nullptr;
SeinCharacter * g_pSeinCharacter = nullptr;

// can't do this, do in ctor
unsigned long long *gp_qwUnityEngineTargetFrameRatePtr = nullptr;


PlaybackManager::PlaybackManager(const char *pcszFileName)
{
	// NativeInjectionEntryPoint sets the base addr before this happens, we're good to do this here now
	*(unsigned long long*)(&UnityEngine_SetTimeScale) = (UnityPlayer_BaseAddr) + UNITYENGINE_SETTIMESCALE_NEWPATCH_RVA;
	*(unsigned long long*)(&UnityEngine_SetVSyncCount) = (UnityPlayer_BaseAddr) + UNITYENGINE_SETVSYNCCOUNT_NEWPATCH_RVA;
	*(unsigned long long*)(&UnityEngine_SetMaximumDeltaTime) = (UnityPlayer_BaseAddr) + UNITYENGINE_SETMAXIMUMDELTATIME_NEWPATCH_RVA;
	gp_qwUnityEngineTargetFrameRatePtr = (unsigned long long*)((UnityPlayer_BaseAddr)+UNITYENGINE_TARGETFRAMERATE_NEWPATCH_RVA);
	this->CurrentFrameRate = 60;

	// Did this somehow set these to null before ? lol
	//g_pDash = g_pJump = g_pGrab = g_pGlide = g_pAbility1 = g_pAbility2 = g_pAbility3 = g_pButtonA = g_pMenuSelect = g_pAbilityWheel = g_pBurrow = g_pBash = g_pGrapple = g_pGrab = nullptr;

	DebugOutput("In PlaybackManager ctor.");
	this->m_nCurrentSeed = 1337;

	this->m_bLoading = false;

	this->m_pGamePadState = nullptr;
	this->m_nTotalFrameCount = 0;
	this->m_Fp = nullptr;
	this->m_bPlayingBack = false;
	memset(&this->m_szCurrentManagerState[0], 0, 800);

	/*
	auto nLen = GetModuleFileNameA(nullptr, this->m_szCurrentDirectory, 256);
	this->m_CWD.assign(this->m_szCurrentDirectory);
	auto indexOfLastBackSlash = this->m_CWD.rfind("\\");
	this->m_CWD.erase(indexOfLastBackSlash + 1, this->m_CWD.length() - indexOfLastBackSlash + 1);
	this->m_CWD += "\\Includes\\";*/

	if (pcszFileName)
	{
		this->m_Fp = _fsopen(pcszFileName, "r", _SH_DENYNO);
	}
	else
	{
		DebugOutput("null filename in PlaybackManager ctor.");
	}

}

void PlaybackManager::SetFrameRate(unsigned int newFrameRate, bool ignoreRetEarly=false)
{
	static constexpr float SixtyFrames = (1.0f / 60.0f);
	//static constexpr float ThreeFrames = (1.0 / 3.0f);
	bool returnEarly = (this->CurrentFrameRate == newFrameRate);
	this->CurrentFrameRate = newFrameRate;

	if (returnEarly && !ignoreRetEarly)
		return;

	UnityEngine_SetTimeScale(1.0f);
	GetPhysicsSettings()->m_CaptureFramerate = 60;
	*gp_qwUnityEngineTargetFrameRatePtr = newFrameRate;
	SetFixedDeltaTime(SixtyFrames);

	// ThreeFrames
	UnityEngine_SetMaximumDeltaTime(SixtyFrames);
	UnityEngine_SetVSyncCount(0);

}

bool PlaybackManager::ReadInputFile()
{
	char LineBuffer[2048] = { 0 };
	unsigned int linecount = 0;

	if (this->m_Fp == nullptr)
	{
		DebugOutput("No input file handle.");
		return false;
	}


	rewind(this->m_Fp);

	this->m_Inputs.clear();


	while (true)
	{
		if (fgets(LineBuffer, 2048, this->m_Fp) == NULL)
			break;

		LineBuffer[strcspn(LineBuffer, "\n")] = 0;

		if (strlen(LineBuffer) == 0)
		{
			++linecount;
			memset(LineBuffer, 0, sizeof(LineBuffer) / sizeof(LineBuffer[0]));
			continue;
		}


		if (LineBuffer[0] == '#')
		{
			// still increase our linecount
			++linecount;
			memset(LineBuffer, 0, sizeof(LineBuffer) / sizeof(LineBuffer[0]));
			continue;
		}


		std::string stringBuffer(LineBuffer);
		unsigned long long indexRunto = stringBuffer.find("Runto");
		unsigned long long  indexWalkto = stringBuffer.find("Walkto");

		if (indexRunto != std::string::npos)
		{
			//strcpy(this->m_BreakState.m_szCurrentFile, this->m_szDefaultFileName);
			//this->m_BreakState.m_nLineNo = linecount;
			//this->m_BreakState.m_BreakType = eBreakType::BREAKTYPE_FAST;

			this->m_RuntoLineNo = linecount;
			// still increase linecount
			linecount++;
			continue;
		}
		else if (indexWalkto != std::string::npos)
		{
			//strcpy(this->m_BreakState.m_szCurrentFile, this->m_szDefaultFileName);
			//this->m_BreakState.m_nLineNo = linecount;
			//this->m_BreakState.m_BreakType = eBreakType::BREAKTYPE_NORMAL;

			this->m_WalktoLineNo = linecount;
			// still increase linecount
			linecount++;

			continue;
		}


		InputRecord * p = new InputRecord(std::string(LineBuffer), ++linecount);

		// invalid InputRecord.
		if (p->m_Frames == -1)
		{
			// free this crap, get it out of here
			delete p;
			memset(LineBuffer, 0, sizeof(LineBuffer) / sizeof(LineBuffer[0]));
			continue;
		}

		this->m_nTotalFrameCount += p->m_Frames;
		this->m_Inputs.push_back(p);
		memset(LineBuffer, 0, sizeof(LineBuffer) / sizeof(LineBuffer[0]));
	}

	return true;
}

unsigned long PlaybackManager::GetTotalFrameCount()
{
	return this->m_nTotalFrameCount;
}

void PlaybackManager::InitPlayback(bool bReload = true)
{
	this->m_RuntoLineNo = -1;
	this->m_WalktoLineNo = -1;
	this->m_nTotalFrameCount = 0;
	//this->m_BreakState.m_nLineNo = -1;

	if (this->m_bPlayingBack && bReload)
	{
		memset(&this->m_szCurrentManagerState[0], 0, 800);
		this->m_bPlayingBack = false;
		return;
	}

	memset(&this->m_szCurrentManagerState[0], 0, 800);
	this->SetFrameRate(60, true);

	bool result = this->ReadInputFile();

	if (!result)
	{
		DebugOutput("Failed to read input file.");
		return;
	}

	this->m_bPlayingBack = true;

	this->m_CurrentFrame = 0;
	this->m_InputIndex = 0;


	if (this->m_Inputs.size() > 0)
	{
		this->m_pCurrentInput = this->m_Inputs[0];
		this->m_FrameToNext = m_pCurrentInput->m_Frames;
	}
	else
	{
		DebugOutput("!Inputs.size");
		this->m_FrameToNext = 1;
		// Disable playback

		this->m_bPlayingBack = false;
		return;
	}

}

unsigned long PlaybackManager::ReloadPlayback()
{
	// Save it
	unsigned long dwPlayedBackFrames = this->m_CurrentFrame;
	this->InitPlayback(false);

	// Restore it
	this->m_CurrentFrame = dwPlayedBackFrames;

	// Step on the index until we get  back to where we were.
	while (this->m_CurrentFrame > this->m_FrameToNext)
	{
		if (this->m_InputIndex + 1 >= this->m_Inputs.size())
		{
			this->m_InputIndex++;
			return this->m_Inputs.size();
		}

		this->m_pCurrentInput = this->m_Inputs[++this->m_InputIndex];
		this->m_FrameToNext += this->m_pCurrentInput->m_Frames;
	}

	return this->m_Inputs.size();
}

bool PlaybackManager::IsPlayingBack()
{
	return this->m_bPlayingBack;
}

unsigned long PlaybackManager::GetCurrentInputIndex()
{
	return this->m_InputIndex;
}

unsigned long PlaybackManager::GetCurrentSeed()
{
	return this->m_CurrentSeed;
}

bool PlaybackManager::IsGameLoading()
{
	InstantLoadScenesController * pInstantLoadScenesInstance = GetInstanceLoadScenesControllerInstance();
	ScenesManager * pScenesManagerInstance = GetScenesManagerInstance();
	GameController * pGameControllerInstance = GetGameControllerInstance();
	SeinCharacter * pSeinCharacter = GetSeinCharacter();
	Vector3 characterPositionOutVector;
	Vector3 currentPosition;

	Vector3 * pCurrentPosition = nullptr;

	if (!pScenesManagerInstance)
	{
		DebugOutput("ScenesManager instance is null.");
		return false;
	}

	if (!pInstantLoadScenesInstance)
	{
		DebugOutput("InstantLoadScenesController instance is null.");
		return false;
	}

	if (pSeinCharacter)
	{
		pCurrentPosition = SeinCharacter_GetPosition(&characterPositionOutVector, pSeinCharacter);
	}
	else
	{
		currentPosition.Set(pScenesManagerInstance->m_CurrentCameraTargetPosition.m_fX, pScenesManagerInstance->m_CurrentCameraTargetPosition.m_fY, 0.0f);
		pCurrentPosition = &currentPosition;
	}

	bool result = pInstantLoadScenesInstance->m_IsLoading && pGameControllerInstance->m_bIsLoadingGame || ScenesManager_IsPositionInsideSceneStillLoading(pScenesManagerInstance, pCurrentPosition);
	
	return result;
}

#pragma warning(disable : 4996)
void PlaybackManager::DoPlayback(bool wasFramestepped, Vector2 * cursorPosFromFixedUpdate)
{

	if (!this->m_bPlayingBack)
	{
		memset(&this->m_szCurrentManagerState[0], 0, 800);
		return;
	}


	if (wasFramestepped)
		memset(&this->m_szCurrentManagerState[0], 0, 800);

	bool isLoading = this->IsGameLoading();

	if (isLoading)
	{
		// lot of sprintf calls, but okay
		memset(&this->m_szCurrentManagerState[0], 0, 800);
		sprintf(this->m_szCurrentManagerState, "L O A D I N G");
		return;
	}

	if (this->m_InputIndex < this->m_Inputs.size())
	{
		if (wasFramestepped)
		{
			unsigned long OldInputDoneCount = m_pCurrentInput->m_Done;
			unsigned long ReloadedCount = this->ReloadPlayback();
			m_pCurrentInput->m_Done += OldInputDoneCount;
		}

		if (this->m_CurrentFrame >= this->m_FrameToNext)
		{
			if (this->m_InputIndex + 1 >= this->m_Inputs.size())
			{
				if (wasFramestepped)
				{
					unsigned long ReloadedCountScope2 = this->ReloadPlayback();
					if (this->m_InputIndex + 1 >= ReloadedCountScope2)
					{
						this->m_InputIndex++;

						// disable playback
						this->m_bPlayingBack = false;
						DebugOutput("Index+1 > ReloadedScope, playback done.");
						memset(&this->m_szCurrentManagerState[0], 0, 800);

						return;
					}
				}
				else
				{
					if (this->m_InputIndex + 1 >= this->m_Inputs.size())
					{
						this->m_InputIndex++;

						// Disable playback
						this->m_bPlayingBack = false;
						DebugOutput("Index+1 > inputSize, playback done.");
						memset(&this->m_szCurrentManagerState[0], 0, 800);

						return;
					}
				}

			} // index + 1 > = inputs.size() scope end

			this->m_pCurrentInput = this->m_Inputs[++this->m_InputIndex];


			// Breakpoints
			if (this->m_RuntoLineNo != -1)
			{
				if (m_pCurrentInput->m_nLineNo < this->m_RuntoLineNo)
				{
					// change SetFrameRate to higher if you can handle the playback speed
					if (m_pCurrentInput->IsSlow())
						this->SetFrameRate(60);
					else
						this->SetFrameRate(300);
				}
				else
				{
					this->m_RuntoLineNo = -1;
					this->SetFrameRate(60);
					g_bPaused = true;
				
				}
			}
			else if (this->m_WalktoLineNo != -1)
			{
				if (m_pCurrentInput->m_nLineNo < this->m_WalktoLineNo)
					;
					//g_GameSpeed = 1;
				else
				{
					this->m_WalktoLineNo = -1;
					g_bPaused = true;
					//g_GameSpeed = 1;
				}
			}


			this->m_FrameToNext += this->m_pCurrentInput->m_Frames;
		} // frame to next scope end
		else
		{
			this->m_pCurrentInput->m_Done++;
		}

		if (this->m_pCurrentInput->HasSeed)
			this->m_nCurrentSeed = this->m_pCurrentInput->m_nSeed;

		//  Increase current frame.
		this->m_CurrentFrame++;

		GetFixedRandomInstance()->FixedUpdateIndex = (this->m_nCurrentSeed + this->m_CurrentFrame);

		g_pCoreInput->HorizontalAnalogLeft = m_pCurrentInput->XAxis;
		g_pCoreInput->Horizontal = m_pCurrentInput->XAxis;

		g_pCoreInput->VerticalAnalogLeft = m_pCurrentInput->YAxis;
		g_pCoreInput->Vertical = m_pCurrentInput->YAxis;

		// These do anything?
		g_pCoreInput->HorizontalMenu = m_pCurrentInput->XAxis;
		g_pCoreInput->VerticalMenu = m_pCurrentInput->YAxis;

		g_pCoreInput->HorizontalAnalogRight = 0.0f;
		g_pCoreInput->VerticalAnalogRight = 0.0f;
		g_pCoreInput->HorizontalDigiPad = (int)m_pCurrentInput->XAxis;
		g_pCoreInput->VerticalDigiPad = (int)m_pCurrentInput->YAxis;

		// BF tas did !HasPos before this? :think:
		if (m_pCurrentInput->HasMouse && !m_pCurrentInput->HasPos)
		{
			g_pCoreInput->CursorPosition.m_fX = m_pCurrentInput->MousePosX;
			g_pCoreInput->CursorPosition.m_fY = m_pCurrentInput->MousePosY;
			g_pCoreInput->CursorMoved = true;
			GetGameSettingsInstance()->m_CurrentControlScheme = EControlScheme::KeyboardAndMouse;
		}
		else
		{
			g_pCoreInput->CursorPosition.m_fX = cursorPosFromFixedUpdate->m_fX;
			g_pCoreInput->CursorPosition.m_fY = cursorPosFromFixedUpdate->m_fY;
			g_pCoreInput->CursorMoved = false;
			GetGameSettingsInstance()->m_CurrentControlScheme = EControlScheme::Controller;
		}

		auto pCmd = GetCmdInstance();

		pCmd->MenuSelect->Update(m_pCurrentInput->IsJump());
		pCmd->Jump->Update(m_pCurrentInput->IsJump());
		pCmd->MenuClose->Update(m_pCurrentInput->IsUnpause());
		pCmd->Ability1->Update(m_pCurrentInput->IsAbilityOne());
		pCmd->Ability2->Update(m_pCurrentInput->IsAbilityTwo());
		pCmd->Ability3->Update(m_pCurrentInput->IsAbilityThree());
		pCmd->OpenWeaponWheel->Update(m_pCurrentInput->IsAbilityWheel());
		pCmd->Dash->Update(m_pCurrentInput->IsDash());
		pCmd->Bash->Update(m_pCurrentInput->IsBash());
		pCmd->Grab->Update(m_pCurrentInput->IsGlide());
		pCmd->Glide->Update(m_pCurrentInput->IsGlide());

		Vector3 tempOut;
		Vector3 tempOut2;
		auto pSeinChar = GetSeinCharacter();

		Vector3 * charPos = pSeinChar->GetRigidbodyPosition();
		Vector3 * pCharSpeed = pSeinChar->GetRigidbodyVelocity();
	
		std::string CharacterStateInfo = "";

		if (pSeinChar->pPlatformBehaviour->pPlatformMovement->m_pOnGround->IsOn)
			CharacterStateInfo += "Grounded, ";


		if (pSeinChar->pPlatformBehaviour->pPlatformMovement->m_pCeiling->IsOn)
			CharacterStateInfo += "OnCeiling, ";

		if (pSeinChar->IsFalling())
			CharacterStateInfo += "Falling, ";

		if(pSeinChar->m_pAbilities->DashNewWrapper->State != nullptr)
			if (SeinDashNew_CanDash(pSeinChar->m_pAbilities->DashNewWrapper->State))
				CharacterStateInfo += "CanDash";

		if(pSeinChar->m_pAbilities->WallJumpWrapper->State != nullptr)
			if (SeinWallJump_CanPerformWallJump(pSeinChar->m_pAbilities->WallJumpWrapper->State))
				CharacterStateInfo += "CanWallJump, ";

		// Done / Frames
		sprintf(this->m_szCurrentManagerState, "Ln: %u (%u / %u) - [%s]\n(Cur:%u / Total:%u)\nRNG: %u\nCursor: %f, %f\nPosition: %f, %f\nSpeed: %f, %f\nCharInfo: %s", this->m_pCurrentInput->m_nLineNo, this->m_pCurrentInput->m_Done, this->m_pCurrentInput->m_Frames,
			this->m_pCurrentInput->ToString().c_str(), this->m_CurrentFrame, this->m_nTotalFrameCount, GetFixedRandomInstance()->FixedUpdateIndex, g_pCoreInput->CursorPosition.m_fX, g_pCoreInput->CursorPosition.m_fY,
			charPos->x, charPos->y, pCharSpeed->x, pCharSpeed->y, CharacterStateInfo.c_str());

		if (m_pCurrentInput->HasPos)
		{
			/*
               TODO: See if setting kinematicism and then disabling it afterwards
		             can make this more consistent.
            */
			tempOut.x = m_pCurrentInput->xPos;
			tempOut.y = m_pCurrentInput->yPos;

			// thought maybe this would help pos sets, but nope, they're still fucked
			pSeinChar->pPlatformBehaviour->pPlatformMovement->m_PreviousPosition.x = tempOut.x;
			pSeinChar->pPlatformBehaviour->pPlatformMovement->m_PreviousPosition.y = tempOut.y;

			// whatever the heck it was, before
			tempOut.z = charPos->z;

			// TODO: Set to Rigidbody pointer directly
			SeinCharacter_SetPosition(GetSeinCharacter(), &tempOut);
		}

		if (m_pCurrentInput->HasKinematicSetting)
		{
			bool kinEnabled = (m_pCurrentInput->Kinematicism == KINEMATIC_ENABLED);
			Rigidbody_SetIsKinematic(GetSeinCharacter()->pPlatformBehaviour->pPlatformMovement->m_pRigidbody, kinEnabled);
		}

	}

	return;
}

inline void PlaybackManager::PlaybackFormatAll()
{
	Vector3 tempOut;
	Vector3 tempOut2;
	auto pSeinChar = GetSeinCharacter();
	Vector3 * charPos = SeinCharacter_GetPosition(&tempOut, pSeinChar);

	// I think there's "AdditiveSpeed" now, maybe you should just look at that,
	// instead of calling this function each framestep, or etc.
	//&pSeinChar->pPlatformBehaviour->pPlatformMovement->m_LocalSpeed;
	Vector3 * pCharSpeed = CharPlatformMovement_GetRigidbodyVelocity(&tempOut2, pSeinChar->pPlatformBehaviour->pPlatformMovement);

	// Done / Frames
	sprintf(this->m_szCurrentManagerState, "Ln: %u (%u / %u) - [%s]\n(Cur:%u / Total:%u)\nCursor: %f, %f\nPosition: %f, %f\nSpeed: %f, %f", this->m_pCurrentInput->m_nLineNo, this->m_pCurrentInput->m_Done, this->m_pCurrentInput->m_Frames,
		this->m_pCurrentInput->ToString().c_str(), this->m_CurrentFrame, this->m_nTotalFrameCount, g_pCoreInput->CursorPosition.m_fX, g_pCoreInput->CursorPosition.m_fY,
		charPos->x, charPos->y, pCharSpeed->x, pCharSpeed->y);
}

void PlaybackManager::FormatWithoutPlayback()
{

	// This crash me?
	memset(&this->m_szCurrentManagerState[0], 0, 800);

	Vector3 tempOut;
	Vector3 tempOut2;
	auto pSeinChar = GetSeinCharacter();

	if (!g_pCoreInput)
		return;

	if (!pSeinChar)
		return;

	Vector3 * charPos = pSeinChar->GetRigidbodyPosition();
	Vector3 * pCharSpeed = pSeinChar->GetRigidbodyVelocity();

	if (!pCharSpeed)
		return;
	
	std::string CharacterStateInfo = "";

	if (pSeinChar->pPlatformBehaviour->pPlatformMovement->m_pOnGround->IsOn)
		CharacterStateInfo += "Grounded, ";

	if (pSeinChar->pPlatformBehaviour->pPlatformMovement->m_pCeiling->IsOn)
		CharacterStateInfo += "OnCeiling, ";

	if (pSeinChar->IsFalling())
		CharacterStateInfo += "Falling, ";

	if (pSeinChar->IsOnWall())
		CharacterStateInfo += "OnWall, ";
	 
	if(pSeinChar->m_pAbilities->DashNewWrapper->State != nullptr)
		if (SeinDashNew_CanDash(pSeinChar->m_pAbilities->DashNewWrapper->State))
			CharacterStateInfo += "CanDash, ";

	if(pSeinChar->m_pAbilities->WallJumpWrapper->State != nullptr)
		if (SeinWallJump_CanPerformWallJump(pSeinChar->m_pAbilities->WallJumpWrapper->State))
			CharacterStateInfo += "CanWallJump, ";

	sprintf(this->m_szCurrentManagerState, "RNG: %u\nCursor: %f, %f\nPosition: %f, %f\nSpeed: %f, %f\nCharStateInfo: %s",
		GetFixedRandomInstance()->FixedUpdateIndex,
		g_pCoreInput->CursorPosition.m_fX, g_pCoreInput->CursorPosition.m_fY, charPos->x, charPos->y,
		pCharSpeed->x, pCharSpeed->y, CharacterStateInfo.c_str());
}

InputRecord * PlaybackManager::GetCurrentInput()
{
	return this->m_pCurrentInput;
}

InputRecord * PlaybackManager::GetCurrentInputIndexBased()
{
	return (this->m_InputIndex == this->m_Inputs.size()) ? nullptr : this->m_Inputs[this->m_InputIndex];
}

XINPUT_STATE * PlaybackManager::GetXInputState()
{
	return this->m_pGamePadState;
}



