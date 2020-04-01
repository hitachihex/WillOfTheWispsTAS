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
		this->m_bPlayingBack = false;
		return;
	}

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
void PlaybackManager::DoPlayback(bool wasFramestepped /* XINPUT_STATE*pxInpState*/)
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

						return;
					}
				}

			} // index + 1 > = inputs.size() scope end

			this->m_pCurrentInput = this->m_Inputs[++this->m_InputIndex];

			// RNG, fast forward, other stuff here, etc



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

		//  Increase current frame.
		this->m_CurrentFrame++;

		g_pCoreInput->HorizontalAnalogLeft = m_pCurrentInput->XAxis;
		g_pCoreInput->Horizontal = m_pCurrentInput->XAxis;

		g_pCoreInput->VerticalAnalogLeft = m_pCurrentInput->YAxis;
		g_pCoreInput->Vertical = m_pCurrentInput->YAxis;

		g_pCoreInput->HorizontalAnalogRight = 0.0f;
		g_pCoreInput->VerticalAnalogRight = 0.0f;
		g_pCoreInput->HorizontalDigiPad = (int)m_pCurrentInput->XAxis;
		g_pCoreInput->VerticalDigiPad = (int)m_pCurrentInput->YAxis;

		/*
		if (!m_pCurrentInput->HasPos)
		{
			g_pCoreInput->CursorMoved=true;
		}*/

		// For now, let's see if it just lets us choose angles.
		g_pCoreInput->CursorMoved = false;
		GetGameSettingsInstance()->m_CurrentControlScheme = EControlScheme::Controller;


		g_pButtonA->Update(m_pCurrentInput->IsJump());
		g_pButtonX->Update(m_pCurrentInput->IsAbilityOne());
		g_pButtonY->Update(m_pCurrentInput->IsAbilityTwo());
		g_pButtonB->Update(m_pCurrentInput->IsAbilityThree());

		g_pMenuSelect->Update(m_pCurrentInput->IsJump());
		g_pPause->Update(m_pCurrentInput->IsStart());
		g_pMenuClose->Update(m_pCurrentInput->IsUnpause());

		g_pJump->Update(m_pCurrentInput->IsJump());
		g_pAbility1->Update(m_pCurrentInput->IsAbilityOne());
		g_pAbility2->Update(m_pCurrentInput->IsAbilityTwo());
		g_pAbility3->Update(m_pCurrentInput->IsAbilityThree());

		g_pAbilityWheel->Update(m_pCurrentInput->IsAbilityWheel());
		g_pDash->Update(m_pCurrentInput->IsDash());
		g_pBash->Update(m_pCurrentInput->IsBash());
		g_pGrapple->Update(m_pCurrentInput->IsGrapple());
		g_pGrab->Update(m_pCurrentInput->IsGlide());
		g_pGlide->Update(m_pCurrentInput->IsGlide());

		Vector3 tempOut;
		Vector3 tempOut2;
		auto pSeinChar = GetSeinCharacter();
		Vector3 * charPos = SeinCharacter_GetPosition(&tempOut, pSeinChar);

		// I think there's "AdditiveSpeed" now, maybe you should just look at that,
		// instead of calling this function each framestep
		//&pSeinChar->pPlatformBehaviour->pPlatformMovement->m_LocalSpeed;
		Vector3 * pCharSpeed = CharPlatformMovement_GetRigidbodyVelocity(&tempOut2, pSeinChar->pPlatformBehaviour->pPlatformMovement);
	
		// Done / Frames
		sprintf(this->m_szCurrentManagerState, "Ln: %u (%u / %u) - [%s]\n(Cur:%u / Total:%u)\nCursor: %f, %f\nPosition: %f, %f\nSpeed: %f, %f", this->m_pCurrentInput->m_nLineNo, this->m_pCurrentInput->m_Done, this->m_pCurrentInput->m_Frames,
			this->m_pCurrentInput->ToString().c_str(), this->m_CurrentFrame, this->m_nTotalFrameCount, g_pCoreInput->CursorPosition.m_fX, g_pCoreInput->CursorPosition.m_fY,
			charPos->x, charPos->y, pCharSpeed->x, pCharSpeed->y);

		if (m_pCurrentInput->HasPos)
		{
			tempOut.x = m_pCurrentInput->xPos;
			tempOut.y = m_pCurrentInput->yPos;

			// thought maybe this would help pos sets, but nope, they're still fucked
			pSeinChar->pPlatformBehaviour->pPlatformMovement->m_PreviousPosition.x = tempOut.x;
			pSeinChar->pPlatformBehaviour->pPlatformMovement->m_PreviousPosition.y = tempOut.y;

			// whatever the heck it was, before
			tempOut.z = charPos->z;
			SeinCharacter_SetPosition(GetSeinCharacter(), &tempOut);
		}
		/*
		sprintf(this->m_szCurrentManagerState, "[%s]-Ln: %u (%u / %u) - [%s]\n(Cur:%u / Total:%u)",
			this->m_pCurrentInput->m_szFromFile,
			(m_pCurrentInput->m_bMultiLevelFile) ? this->m_pCurrentInput->m_nInternalLineNo : this->m_pCurrentInput->m_nLineNo,
			this->m_pCurrentInput->m_Done, this->m_pCurrentInput->m_Frames,
			this->m_pCurrentInput->ToString().c_str(), this->m_CurrentFrame, this->m_nTotalFrameCount);*/

			// Packet number is our current frame.
		//pxInpState->dwPacketNumber = this->m_CurrentFrame;

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

	Vector3 tempOut;
	Vector3 tempOut2;
	auto pSeinChar = GetSeinCharacter();

	if (!g_pCoreInput)
		return;

	if (!pSeinChar)
		return;

	Vector3 * charPos = SeinCharacter_GetPosition(&tempOut, pSeinChar);
	Vector3 * pCharSpeed = CharPlatformMovement_GetRigidbodyVelocity(&tempOut2, pSeinChar->pPlatformBehaviour->pPlatformMovement);

	if (!pCharSpeed)
		return;
	
	// its annoying to see the doubles when this doesn't clear our string..
	// how to fix?
	sprintf(this->m_szCurrentManagerState, "Cursor: %f, %f\nPosition: %f, %f\nSpeed: %f, %f",
		g_pCoreInput->CursorPosition.m_fX, g_pCoreInput->CursorPosition.m_fY, charPos->x, charPos->y,
		pCharSpeed->x, pCharSpeed->y);
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



