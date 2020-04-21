// WOTW.TAS.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Addresses.h"
#include <limits.h>
#include "EasyHookUtils.h"
#include "WOTW.TAS.h"
#include "ConfigurationManager.h"
#include <stdlib.h>
#include <time.h>



unsigned long g_ACLEntries[1] = { 0 };
extern "C" void __declspec(dllexport) __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* inRemoteInfo);

oXInputGetState original_XInputGetState = (oXInputGetState)(0x0);
HOOK_TRACE_INFO WOTW_UnityEngine_GetDeltaTime_HookHandle = { NULL };
HOOK_TRACE_INFO WOTW_UnityEngine_PlayerLoopInternal_HookHandle = { NULL };
HOOK_TRACE_INFO WOTW_CompoundButtonInput_GetButton_HookHandle = { NULL };

// Can't do this here
oWOTW_UnityEngine_GeltaDeltaTime original_WOTW_UnityEngine_GetDeltaTime = (oWOTW_UnityEngine_GeltaDeltaTime)(0x0);

// Can't do this here
oil2cpp_runtime_invoke original_il2cpp_runtime_invoke = (oil2cpp_runtime_invoke)(0x0);

// Can't do this here
oWOTW_UnityEngine_PlayerLoopInternal original_WOTW_UnityEngine_PlayerLoopInternal = (oWOTW_UnityEngine_PlayerLoopInternal)(0x0);


// This gets set in the Injection Entry Point, so it's fine.
oCompoundButtonInput_GetButton original_CompoundButton_GetButton = (oCompoundButtonInput_GetButton)(0x0);
oInputButtonProcessor_GetButton original_InputButtonProcessor_GetButton = (oInputButtonProcessor_GetButton)(0x0);
oInputButtonProcessor_GetCommand original_InputButtonProcessor_GetCommand = (oInputButtonProcessor_GetCommand)(0x0);
oPlayerInput_RefreshControls orig_PlayerInput_RefreshControls = (oPlayerInput_RefreshControls)(0x0);

// These would get set in the runtime_invoke hook
oPlayerInput_FixedUpdate original_PlayerInputFixedUpdate = (oPlayerInput_FixedUpdate)(0x0);
oGameController_FixedUpdate original_GameControllerFixedUpdate = (oGameController_FixedUpdate)(0x0);

// Done in PlaybackManager.h and .cpp instead.
//fnSeinCharacter_GetPosition SeinCharacter_GetPosition = (fnSeinCharacter_GetPosition)(0x0);

oUnityEngine_GetMousePositionInjected original_UnityEngine_GetMousePositonInjected = (oUnityEngine_GetMousePositionInjected)(0x0);

// Do this in InjectionEntryPoint.
fnScreenToViewportPoint_Injected ScreenToViewportPoint_Injected = (fnScreenToViewportPoint_Injected)(0x0);
unsigned long long PlayerInput_FixedUpdate_VA = 0x0;
void __stdcall NativeInjectionEntryPoint(REMOTE_ENTRY_INFO* inRemoteInfo)
{
	
	
	Assembly_BaseAddr = (unsigned long long)GetModuleHandleA("GameAssembly.dll");
	UnityPlayer_BaseAddr = (unsigned long long)GetModuleHandleA("UnityPlayer.dll");

	// Patch GameController::OnApplicationFocus
	ApplyPatch((Assembly_BaseAddr)+0x49EC5B, "\xFF\xC5\x90", 0x03);

	String::Set(g_pTextAreaString, L"Temporary String");
	String::Set(g_pGUIString, L"Temporary String");
	//String::SetUnknown0(g_pTextAreaString, 1);

	DWORD dwOldProt;
	VirtualProtect((LPVOID)(UnityPlayer_BaseAddr + IL2CPP_RUNTIME_INVOKE_IAT_NEWPATCH_RVA), 8, PAGE_EXECUTE_READWRITE, &dwOldProt);
	*(unsigned long long*)(&original_WOTW_UnityEngine_GetDeltaTime) = (UnityPlayer_BaseAddr)+UNITYENGINE_GETDELTATIME_NEWPATCH_RVA;
	*(unsigned long long*)(&original_il2cpp_runtime_invoke) = *(unsigned long long*)(UnityPlayer_BaseAddr + IL2CPP_RUNTIME_INVOKE_IAT_NEWPATCH_RVA);
	*(unsigned long long*)(UnityPlayer_BaseAddr + IL2CPP_RUNTIME_INVOKE_IAT_NEWPATCH_RVA) = (unsigned long long)il2cpp_runtime_invoke_Hook;

	g_psdwGuiIndexerPtr = (signed long*)((UnityPlayer_BaseAddr) + UNITYPLAYER_GUIINDEXER_SDWORD_RVA);
	g_qwUberStateControllerInstancePtr = ((Assembly_BaseAddr) + GAMEASSEMBLY_UBERSTATECONTROLLER_INSTANCE_RVA);
	g_qwGUILayoutOptionsDefaultInstance = ((Assembly_BaseAddr)+GAMEASSEMBLY_GUILAYOUTOPTIONSINSTANCE_DEFAULT_RVA);
	g_qwGUIInstancePtr = ((Assembly_BaseAddr)+GAMEASSEMBLY_GUIINSTANCE_RVA);
	gqw_CmdInstancePtr = ((Assembly_BaseAddr)+GAMEASSEMBLY_CMDINSTANCE_PTR_RVA);
	gqw_FixedRandomInstancePtr = ((Assembly_BaseAddr)+FIXEDRANDOM_INSTANCEPTR_RVA);
	gqw_SeinCharacterPtr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr)+CHARACTERS_GETSEIN_NEWPATCH_RVA, 0x86));

	// what?
	gqw_GameSettingsInstance_Ptr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr)+PLAYERINPUT_GETWASKEYBOARDUSEDLAST_NEWPATCH_RVA, 0x65));
	gqw_GameSettingsInstance_Ptr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr)+UNKNOWN_FUNCTION_OFFSETFORQUALITYSETTINGS_NEWPATCH_RVA, 0x2DF));

	gqw_InstantLoadScenesControllerInstancePtr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr)+INSTANTLOADSCENESCONTROLLER_AWAKE_NEWPATCH_RVA, INSTANTLOADSCENESCONTROLLER_OFFSET_TO_PTR));
	gqw_GameControllerInstancePtr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr)+GAMECONTROLLER_RESETSTATISTICS_NEWPATCH_RVA, GAMECONTROLLERINSTANCE_OFFSET_TO_PTR));
	gqw_ScenesManagerInstancePtr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr)+INSTANTLOADSCENESCONTROLLER_GETSCENESMANAGER_NEWPATCH_RVA, INSTANTLOADSCENESCONTROLLER_OFFSET_TO_SM_PTR));
	gqw_UICamerasInstancePtr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr)+PLAYERINPUT_FIXEDUPDATE_NEWPATCH_RVA, 0xB9));
	gqw_CoreInputInstancePtr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr)+PLAYERINPUT_FIXEDUPDATE_NEWPATCH_RVA, 0x27B));
	g_qwScreenInstancePtr = ((UnityPlayer_BaseAddr) + UNITYPLAYER_SCREENINSTANCE_RVA);
	g_pSeinCharacter = GetSeinCharacter();

	// Because we have no other way to set it.
	*(unsigned long long*)(&GUI_Button) = ((Assembly_BaseAddr) + GAMEASSEMBLY_GUIBUTTON_RVA);
	*(unsigned long long*)(&SeinComboHandler_IsPerformingAttackAbility) = ((Assembly_BaseAddr) + GAMEASSEMBLY_SEINCOMBOHANDLER_ISPERFORMINGATTACKABILITY_RVA);
	*(unsigned long long*)(&Input_GetMouseButtonUp) = ((UnityPlayer_BaseAddr) + UNITYPLAYER_GETMOUSEBUTTONUP_RVA);
	*(unsigned long long*)(&InternalDoWindowInjected) = ((UnityPlayer_BaseAddr) + UNITYPLAYER_INTERNALDOWINDOWINJECTED_RVA);
	*(unsigned long long*)(&GUI_TextArea) = ((Assembly_BaseAddr) + GAMEASSEMBLY_GUITEXTAREA_RVA);
	*(unsigned long long*)(&GUILabel_ContentAndStyle) = ((Assembly_BaseAddr)+GAMEASSEMBLY_GUILABELCONTENTANDSTYLE_RVA);
	*(unsigned long long*)(&GUI_Label) = ((Assembly_BaseAddr)+GAMEASSEMBLY_GUI_LABEL_RVA);

	*(unsigned long long*)(&GUI_LayoutBeginArea) = ((Assembly_BaseAddr)+GAMEASSEMBLY_GUILAYOUT_BEGINAREA_RVA);
	*(unsigned long long*)(&GUILayout_LabelWithOptions) = ((Assembly_BaseAddr)+GAMEASSEMBLY_GUILAYOUT_LABEL_WITHOPTIONS_RVA);
	*(unsigned long long*)(&GUILayout_EndArea) = ((Assembly_BaseAddr)+GAMEASSEMBLY_GUILAYOUT_ENDAREA_RVA);

	*(unsigned long long*)(&RestrictAbilityController_IsRestricted) = (Assembly_BaseAddr)+GAMEASSEMBLY_RESTRICTABILITYCONTROLLER_ISABILITYRESTRICTED_RVA;
	*(unsigned long long*)(&Rigidbody_GetIsKinematic) = (UnityPlayer_BaseAddr)+UNITYPLAYER_UNITYENGINE_RIGIDBODY_GETISKINEMATIC_RVA;
	*(unsigned long long*)(&Rigidbody_SetIsKinematic) = (UnityPlayer_BaseAddr)+UNITYPLAYER_RIGIDBODY_SETISKINEMATIC_RVA;
	*(unsigned long long*)(&UnityEngine_Animator_GetUpdateMode) = (UnityPlayer_BaseAddr)+UNITYPLAYER_UNITYENGINE_ANIMATOR_GETUPDATEMODE_RVA;
	*(unsigned long long*)(&SeinDashNew_CanDash) = (Assembly_BaseAddr)+SEINDASHNEW_GETCANDASH_RVA;
	*(unsigned long long*)(&SeinWallJump_CanPerformWallJump) = (Assembly_BaseAddr)+SEINWALLJUMP_CANPERFORMWALLJUMP_RVA;
	*(unsigned long long*)(&original_SeinDashNew_OnProcessRootMotion) = (Assembly_BaseAddr)+SEINDASHNEW_ONPROCESSROOTMOTION_RVA;
	*(unsigned long long*)(&original_WOTW_UnityEngine_PlayerLoopInternal) = (UnityPlayer_BaseAddr)+UNITYENGINE_PLAYERLOOPINTERNAL_NEWPATCH_RVA;
	*(unsigned long long*)(&original_UnityEngine_GetMousePositonInjected) = (UnityPlayer_BaseAddr)+UNITYENGINE_GETMOUSEPOSITION_INJECTED_RVA;
	*(unsigned long long*)(&ScreenToViewportPoint_Injected) = (UnityPlayer_BaseAddr)+UNITYENGINE_SCREENTOVIEWPORTPOINTINJECTED_NEWPATCH_RVA;
	*(unsigned long long*)(&original_CompoundButton_GetButton) = (Assembly_BaseAddr)+COMPOUNDBUTTONINPUT_GETBUTTON_RVA;
	*(unsigned long long*)(&original_InputButtonProcessor_GetButton) = (Assembly_BaseAddr)+INPUTBUTTONPROCESSOR_GETBUTTON_NEWPATCH_RVA;
	*(unsigned long long*)(&original_InputButtonProcessor_GetCommand) = (Assembly_BaseAddr)+INPUTBUTTONPROCESSOR_GETCOMMAND_NEWPATCH_RVA;
	*(unsigned long long*)(&SeinCharacter_GetPosition) = (Assembly_BaseAddr)+SEINCHARACTER_GETPOSITION_NEWPATCH_RVA;
	*(unsigned long long*)(&SeinCharacter_SetPosition) = (Assembly_BaseAddr)+SEINCHARACTER_SETPOSITION_NEWPATCH_RVA;
	*(unsigned long long*)(&SeinCharacter_GetLocalSpeed) = (Assembly_BaseAddr)+SEINCHARACTER_GETLOCALSPEED_NEWPATCH_RVA;
	*(unsigned long long*)(&CharPlatformMovement_GetRigidbodyVelocity) = (Assembly_BaseAddr)+CHARPLATFORMMOVEMENT_GETRIGIDBODYVELOCITY_NEWPATCH_RVA;
	*(unsigned long long*)(&ScenesManager_IsPositionInsideSceneStillLoading) = (Assembly_BaseAddr)+SCENESMANAGER_ISPOSITIONINSIDESCENESTILLLOADING_NEWPATCH_RVA;

	*(unsigned long long*)(&orig_PlayerInput_RefreshControls) = (Assembly_BaseAddr)+0x12FC6B0;

	// Patch whatever keeps trying to set the Max Timestep
	ApplyNops((Assembly_BaseAddr)+GAMEASSEMBLY_MAXTIMESTEP_SETCALL_NEWPATCH_RVA, 0x02);

	NTSTATUS result = 0;
	result = AddHook((void*)(UnityPlayer_BaseAddr + UNITYENGINE_PLAYERLOOPINTERNAL_NEWPATCH_RVA), WOTW_UnityEngine_PlayerLoopInternal_Hook, NULL, &WOTW_UnityEngine_PlayerLoopInternal_HookHandle);

	if (FAILED(result))
	{
		auto err = RtlGetLastErrorString();
		DebugOutputW(L"Failed to hook WOTW_UnityEngine_PlayerLoopInternal,err=%s", err);
	}
	else
	{
		DebugOutput("WOTW_UnityEngine_PlayerLoopInternal hook installed.");
		ExclusiveHook(&WOTW_UnityEngine_PlayerLoopInternal_HookHandle);
	}


	result = AddHook((void*)(UnityPlayer_BaseAddr + UNITYENGINE_GETDELTATIME_NEWPATCH_RVA), WOTW_UnityEngine_GetDeltaTime_Hook, NULL, &WOTW_UnityEngine_GetDeltaTime_HookHandle);

	if (FAILED(result))
	{
		auto err = RtlGetLastErrorString();
		DebugOutputW(L"Failed to hook WOTW_UnityEngine_GetDeltaTime,err=%s", err);
	}
	else
	{
		DebugOutput("WOTW_UnityEngine_GetDeltaTime hook installed.");
		ExclusiveHook(&WOTW_UnityEngine_GetDeltaTime_HookHandle);
	}


	g_pPlaybackManager = new PlaybackManager("Ori.rec");
	g_pPlaybackManager->SetFrameRate(60, true, 1.0f);

	if (g_pConfigManager)
	{
		g_pPlaybackManager->m_RuntoFramerate = g_pConfigManager->m_pPlaybackSettingsParser->SettingFromMap<unsigned int>(L"PlaybackSettings", L"RuntoSpeed");
		g_pPlaybackManager->m_fRuntoTimescale = g_pConfigManager->m_pPlaybackSettingsParser->SettingFromMap<float>(L"PlaybackSettings", L"Timescale");
	}
	else
	{
		DebugOutput("ConfigManager hasn't been instantiated before PlaybackManager, hmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm.jpg");
	}
	//*gp_qwUnityEngineTargetFrameRatePtr = g_pPlaybackManager->CurrentFrameRate;
	DumpPointersForExternalOSD();
}


float __fastcall WOTW_UnityEngine_GetDeltaTime_Hook()
{
	static constexpr float SchixtySeven = (float)(1.0f / 60.0f);
	DoOnceBlock("WOTW_UnityEngine_GetDeltaTimeHook, !bOnce");

	return g_fCurrentDeltaTimeSpoof;
}

void * __fastcall il2cpp_runtime_invoke_Hook(MethodInfo* pMethodInfo, void* obj, void ** params, void ** exc)
{
	DoOnceBlock("il2cpp_runtime_invoke_Hook, !bOnce");
	static bool bHookedPlayerInputFixedUpdate = false;
	static bool bHookedGameController_OnGUI = false;
	static bool bHookedGameController_Update = false;
	//static bool bHookedSeinDashNew_OnProcessRootMotion = false;

	if (!bHookedGameController_Update)
	{
		std::string className = pMethodInfo->pClass->pcszClassName;
		std::string methodName = pMethodInfo->pcszMethodName;

		if (className == "GameController" && methodName == "Update")
		{
			*(unsigned long long*)(&orig_GameController_Update) = pMethodInfo->methodAddr;
			pMethodInfo->methodAddr = (unsigned long long)GameController_Update_Hook;
			DebugOutput("Replaced GameController::Update with hook.");
			bHookedGameController_Update = true;
		}
	}

	if (!bHookedPlayerInputFixedUpdate)
	{
		std::string className = pMethodInfo->pClass->pcszClassName;
		std::string methodName = pMethodInfo->pcszMethodName;

		if (className == "PlayerInput" && methodName == "FixedUpdate")
		{
			*(unsigned long long*)(&original_PlayerInputFixedUpdate) = pMethodInfo->methodAddr;
			PlayerInput_FixedUpdate_VA = pMethodInfo->methodAddr;
			pMethodInfo->methodAddr = (unsigned long long)PlayerInput_FixedUpdate_Hook;
			DebugOutput("Replaced PlayerInput::FixedUpdate with hook.");
			bHookedPlayerInputFixedUpdate = true;

		}
	}

	if (!bHookedGameController_OnGUI)
	{
		std::string className = pMethodInfo->pClass->pcszClassName;
		std::string methodName = pMethodInfo->pcszMethodName;

		if (className == "GameController" && methodName == "OnGUI")
		{
			*(unsigned long long*)(&orig_GameController_OnGUI) = pMethodInfo->methodAddr;
			pMethodInfo->methodAddr = (unsigned long long)GameController_OnGUI_Hook;
			DebugOutput("Replaced GameController::OnGUI with hook.");
			bHookedGameController_OnGUI = true;
		}
	}


	return original_il2cpp_runtime_invoke(pMethodInfo, obj, params, exc);
}

void __fastcall WOTW_UnityEngine_PlayerLoopInternal_Hook()
{
	DoOnceBlock("WOTW_UnityEngine_PlayerLoopInternal_Hook, !bOnce");

	// ALSO: These keybinds shouldn't work if the keybinds menu is active
	if (!g_pConfigManager->m_bKeybindsMenuActive)
	{

		// ------------------------
		// No grace checks on these
		// ------------------------
		if (g_pConfigManager->Pause->CheckKeyWithoutGrace(true))
		{
			g_bPaused = !g_bPaused;
			if (g_bPaused)
				DebugOutput("Game Paused.");
			else
				DebugOutput("Game Unpaused.");
		}


		if (g_pConfigManager->Playback->CheckKeyWithoutGrace(true))
		{
			if (g_pPlaybackManager)
			{
				if (g_pPlaybackManager->IsPlayingBack())
				{
					g_pPlaybackManager->InitPlayback(true);
				}
				else
				{
					g_pPlaybackManager->InitPlayback(false);
				}
			}
		}

		if (g_pConfigManager->CopyCursor->CheckKeyWithoutGrace(true))
		{
			if (g_pPlaybackManager)
				g_pPlaybackManager->CopyCursorPosition();
		}
		
		if (g_pConfigManager->CopyPosition->CheckKeyWithoutGrace(true))
		{
			if (g_pPlaybackManager)
				g_pPlaybackManager->CopyPlayerPosition();
		}

		if (g_pConfigManager->CopySpeed->CheckKeyWithoutGrace(true))
		{
			if (g_pPlaybackManager)
				g_pPlaybackManager->CopyPlayerSpeed();
		}
	}

	// Not exempt from grace while not paused :)
	if (g_pConfigManager->ValidTimeToCheckKey() && g_pConfigManager->ToggleOSD->CheckKey(true))
	{
		g_bShowOSD = !g_bShowOSD;
	}
	/*
	if (GetAsyncKeyState(VK_F1) & 1)
	{
		g_bPaused = !g_bPaused;
		if (g_bPaused)
			DebugOutput("Game Paused.");
		else
			DebugOutput("Game Unpaused.");
	}

	if (GetAsyncKeyState(VK_F4) & 1)
	{
		if (g_pPlaybackManager)
		{
			if (g_pPlaybackManager->IsPlayingBack())
			{
				g_pPlaybackManager->InitPlayback(true);
			}
			else
			{
				g_pPlaybackManager->InitPlayback(false);
			}
		}
	}
	
	if (GetAsyncKeyState(VK_F9) & 1)
	{
		g_bShowOSD = !g_bShowOSD;
		// Read in for g_fDeltaTimeSpoof with something else, this is more useful
	}*/

	if(g_bPaused)
	{

		// can't check if it's a valid time to check the key because timers aren't going to update
		// while we're paused :)

		// ToggleOSD needs to be checked without grace while we're paused.
		if (g_pConfigManager->ToggleOSD->CheckKeyWithoutGrace(true))
			g_bShowOSD = !g_bShowOSD;

		// Framestep obviously needs to check without grace, it only works while paused.
		if (g_pConfigManager->Framestep->CheckKeyRaw())
		{
			g_bPressedFrameStepThisFrame = true;
			original_WOTW_UnityEngine_PlayerLoopInternal();

			// Update it all for framestepping.
			if (g_pPlaybackManager)
				g_pPlaybackManager->FormatConditonally();

		}

		/*
		if (g_pConfigManager->Framestep->CheckKeyWithoutGrace(true))
		{
			g_bPressedFrameStepThisFrame = true;
			original_WOTW_UnityEngine_PlayerLoopInternal();

			// Update it all for framestepping.
			if (g_pPlaybackManager && g_pPlaybackManager->IsPlayingBack())
				g_pPlaybackManager->PlaybackFormatWithPlayback();
			else
			{
				if (g_pPlaybackManager)
					g_pPlaybackManager->FormatWithoutPlayback();
			}
		}*/

		return;
	}

	// Update it all when we aren't paused too.
	if (g_pPlaybackManager)
	{
		g_pPlaybackManager->FormatConditonally();
	}

	return original_WOTW_UnityEngine_PlayerLoopInternal();
}

unsigned long WINAPI XInputGetState_Hook(unsigned long dwUserIndex, XINPUT_STATE* pInputState)
{
	DoOnceBlock("XInputGetState_Hook, !bOnce");


	if (!pInputState)
		// return ERROR_SUCCESS;
		return ERROR_DEVICE_NOT_CONNECTED;

	auto * p = &pInputState->Gamepad;

	if (g_pPlaybackManager)
	{
		if (g_pPlaybackManager->IsPlayingBack())
		{
			p->sThumbLX = 0;
			p->sThumbLY = 0;
			p->sThumbRX = 0;
			p->sThumbRY = 0;
			p->wButtons = 0;

			//g_pPlaybackManager->DoPlayback(g_bPressedFrameStepThisFrame, pInputState);
			g_bPressedFrameStepThisFrame = false;

			return ERROR_SUCCESS;
		}
	}

	// Was this necessary, I don't remember?
	p->sThumbLX = 0;
	p->sThumbLY = 0;
	p->sThumbRX = 0;
	p->sThumbRY = 0;
	p->wButtons = 0;

	// So we don't get fucked trying to do shit normally
	return ERROR_DEVICE_NOT_CONNECTED;
}

bool __fastcall CompoundButton_GetButton_Hook(unsigned long long __rcx)
{
	DoOnceBlock("CompoundButton_GetButton_Hook, !bOnce");

	return original_CompoundButton_GetButton(__rcx);
}


void __fastcall PlayerInput_FixedUpdate_Hook2(unsigned long long __rcx)
{
	PlayerInput *pPlayerInput = (PlayerInput*)(__rcx);

	if (!pPlayerInput->m_bActive)
		return;

	// wut? lol
	if (!g_pPlaybackManager)
		return original_PlayerInputFixedUpdate(__rcx);


	Core_Input * pCoreInput = GetCoreInputInstance();
	
	if (!pCoreInput)
		original_PlayerInputFixedUpdate(__rcx);

	// COME ON, MAN.
	g_pCoreInput = pCoreInput;

	// we ain't playing back, kick cans kid
	if (!g_pPlaybackManager->IsPlayingBack())
	{
		// For printing crap when we aren't playing back
		//g_pPlaybackManager->FormatWithoutPlayback();
		return original_PlayerInputFixedUpdate(__rcx);
	}

	UnityEngine_Camera * pCurrentCamera = GetCameras()->m_pCurrent->m_pCameraController->m_pCamera;
	UnityEngine_Input * pUnityEngineInput = GetUnityEngine_Input();
	Vector3 mousePos(pUnityEngineInput->m_fMouseX, pUnityEngineInput->m_fMouseY);

	// our out vector.
	Vector3 viewportPoint;

	// rcx=classptr, rdx=from, r8=outVector
	ScreenToViewportPoint_Injected(pCurrentCamera, &mousePos, &viewportPoint);

	// Don't let it set it ? Or let it, but set it later anyways. should be fine.

	// Don't do this
	//pCoreInput->CursorPosition.m_fX = viewportPoint.x;
	//pCoreInput->CursorPosition.m_fY = viewportPoint.y;

	Vector2 newVPP(viewportPoint.x, viewportPoint.y);
	if (g_pPlaybackManager->IsPlayingBack())
	{
		g_pPlaybackManager->DoPlayback(g_bPressedFrameStepThisFrame, &newVPP);
		orig_PlayerInput_RefreshControls(__rcx);
		g_bPressedFrameStepThisFrame = false;
	}

}


void __fastcall PlayerInput_FixedUpdate_Hook(unsigned long long __rcx)
{

	DoOnceBlock("PlayerInput_FixedUpdate_Hook, !bOnce");

	PlayerInput_FixedUpdate_Hook2(__rcx);
}

void __fastcall GameController_FixedUpdate_Hook(unsigned long long __rcx)
{
	return original_GameControllerFixedUpdate(__rcx);
}

void DumpPointersForExternalOSD()
{
	FILE *fp = nullptr;

	fp = fopen("pointer_ref.txt", "w");

	if (!fp)
		return;

	unsigned long long ** ptrPaused = (unsigned long long**)&g_bPaused;
	unsigned long long ** ptrManagerState = (unsigned long long**)&g_pPlaybackManager->m_szCurrentManagerState[0];

	fprintf(fp, "%llx,%llx", ptrManagerState, ptrPaused);

	fclose(fp);
}

void ApplyNops(unsigned long long addr, unsigned int n)
{
	unsigned long dwOldProt;
	VirtualProtect((LPVOID)addr, n, PAGE_EXECUTE_READWRITE, &dwOldProt);

	unsigned char *pAddr = (unsigned char*)addr;
	for (unsigned int i = 0; i < n; i++)
		pAddr[i] = 0x90;
}

void ApplyPatch(unsigned long long addr, const char * bytes, unsigned int n)
{
	unsigned int len = n;
	unsigned long dwOldProt = 0x0;

	VirtualProtect((LPVOID)addr, len, PAGE_EXECUTE_READWRITE, &dwOldProt);

	for (unsigned int i = 0; i < len; i++)
		*(unsigned char*)(addr + i) = bytes[i];

}
