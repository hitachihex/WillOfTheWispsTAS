// WOTW.TAS.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Addresses.h"
#include <limits.h>
#include "EasyHookUtils.h"
#include "WOTW.TAS.h"
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
	unsigned long long Assembly_BaseAddr = (unsigned long long)GetModuleHandleA("GameAssembly.dll");
	UnityPlayer_BaseAddr = (unsigned long long)GetModuleHandleA("UnityPlayer.dll");


	// Patch GameController::OnApplicationFocus
	ApplyPatch((Assembly_BaseAddr)+0x52191B, "\xFF\xC5\x90");

	DWORD dwOldProt;
	VirtualProtect((LPVOID)(UnityPlayer_BaseAddr + IL2CPP_RUNTIME_INVOKE_IAT_NEWPATCH_RVA), 8, PAGE_EXECUTE_READWRITE, &dwOldProt);
	*(unsigned long long*)(&original_WOTW_UnityEngine_GetDeltaTime) = (UnityPlayer_BaseAddr) + UNITYENGINE_GETDELTATIME_NEWPATCH_RVA;
	*(unsigned long long*)(&original_il2cpp_runtime_invoke) = *(unsigned long long*)(UnityPlayer_BaseAddr + IL2CPP_RUNTIME_INVOKE_IAT_NEWPATCH_RVA);
	*(unsigned long long*)(UnityPlayer_BaseAddr + IL2CPP_RUNTIME_INVOKE_IAT_NEWPATCH_RVA) = (unsigned long long)il2cpp_runtime_invoke_Hook;

	/*
	unsigned long long SeinCharacter_getSein_VA = (Assembly_BaseAddr) + CHARACTERS_GETSEIN_NEWPATCH_RVA;
	unsigned long long SeinCharacter_VAToInstruction = (SeinCharacter_getSein_VA + 0x86);
	unsigned long long SeinCharacter_relativeCalc = *(unsigned long*)(SeinCharacter_VAToInstruction + 0x03);
	unsigned long long ptr_SeinCharacter = (SeinCharacter_VAToInstruction + SeinCharacter_relativeCalc) + 0x07;

	gqw_SeinCharacterPtr = (ptr_SeinCharacter);*/

	gqw_SeinCharacterPtr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr) + CHARACTERS_GETSEIN_NEWPATCH_RVA, 0x86));
	gqw_GameSettingsInstance_Ptr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr) + PLAYERINPUT_GETWASKEYBOARDUSEDLAST_NEWPATCH_RVA, 0x65));
	gqw_GameSettingsInstance_Ptr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr) + UNKNOWN_FUNCTION_OFFSETFORQUALITYSETTINGS_NEWPATCH_RVA, 0x2DF));
	gqw_InstantLoadScenesControllerInstancePtr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr)+INSTANTLOADSCENESCONTROLLER_AWAKE_NEWPATCH_RVA, INSTANTLOADSCENESCONTROLLER_OFFSET_TO_PTR));
	gqw_GameControllerInstancePtr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr)+GAMECONTROLLER_RESETSTATISTICS_NEWPATCH_RVA, GAMECONTROLLERINSTANCE_OFFSET_TO_PTR));
	gqw_ScenesManagerInstancePtr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr)+INSTANTLOADSCENESCONTROLLER_GETSCENESMANAGER_NEWPATCH_RVA, INSTANTLOADSCENESCONTROLLER_OFFSET_TO_SM_PTR));
	gqw_UICamerasInstancePtr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr) + PLAYERINPUT_FIXEDUPDATE_NEWPATCH_RVA, 0xB9));
	gqw_CoreInputInstancePtr = (RelativeAddressCalcFromDatasegment((Assembly_BaseAddr)+PLAYERINPUT_FIXEDUPDATE_NEWPATCH_RVA, 0x27B));
	g_pSeinCharacter = GetSeinCharacter();

	// Because we have no other way to set it.
	*(unsigned long long*)(&original_WOTW_UnityEngine_PlayerLoopInternal) = (UnityPlayer_BaseAddr) + UNITYENGINE_PLAYERLOOPINTERNAL_NEWPATCH_RVA;
	*(unsigned long long*)(&original_UnityEngine_GetMousePositonInjected) = (UnityPlayer_BaseAddr)+ UNITYENGINE_GETMOUSEPOSITION_INJECTED_RVA;
	*(unsigned long long*)(&ScreenToViewportPoint_Injected) = (UnityPlayer_BaseAddr) + UNITYENGINE_SCREENTOVIEWPORTPOINTINJECTED_NEWPATCH_RVA;
	*(unsigned long long*)(&original_CompoundButton_GetButton) = (Assembly_BaseAddr) + COMPOUNDBUTTONINPUT_GETBUTTON_RVA;
	*(unsigned long long*)(&original_InputButtonProcessor_GetButton) = (Assembly_BaseAddr) + INPUTBUTTONPROCESSOR_GETBUTTON_NEWPATCH_RVA;
	*(unsigned long long*)(&original_InputButtonProcessor_GetCommand) = (Assembly_BaseAddr) + INPUTBUTTONPROCESSOR_GETCOMMAND_NEWPATCH_RVA;
	*(unsigned long long*)(&SeinCharacter_GetPosition) = (Assembly_BaseAddr) + SEINCHARACTER_GETPOSITION_NEWPATCH_RVA;
	*(unsigned long long*)(&SeinCharacter_SetPosition) = (Assembly_BaseAddr) + SEINCHARACTER_SETPOSITION_NEWPATCH_RVA;
	*(unsigned long long*)(&SeinCharacter_GetLocalSpeed) = (Assembly_BaseAddr) + SEINCHARACTER_GETLOCALSPEED_NEWPATCH_RVA;
	*(unsigned long long*)(&CharPlatformMovement_GetRigidbodyVelocity) = (Assembly_BaseAddr) + CHARPLATFORMMOVEMENT_GETRIGIDBODYVELOCITY_NEWPATCH_RVA;
	*(unsigned long long*)(&ScenesManager_IsPositionInsideSceneStillLoading) = (Assembly_BaseAddr) + SCENESMANAGER_ISPOSITIONINSIDESCENESTILLLOADING_NEWPATCH_RVA;

	*(unsigned long long*)(&orig_PlayerInput_RefreshControls) = (Assembly_BaseAddr) + 0x12F8400;

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

	
	result = AddHook((void*)(UnityPlayer_BaseAddr + UNITYENGINE_GETDELTATIME_NEWPATCH_RVA),WOTW_UnityEngine_GetDeltaTime_Hook, NULL, &WOTW_UnityEngine_GetDeltaTime_HookHandle);

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
	g_pPlaybackManager->SetFrameRate(60, true);
	//*gp_qwUnityEngineTargetFrameRatePtr = g_pPlaybackManager->CurrentFrameRate;
	DumpPointersForExternalOSD();
}


float __fastcall WOTW_UnityEngine_GetDeltaTime_Hook()
{
	static constexpr float SchixtySeven = (float)(1.0f / 60.0f);
	DoOnceBlock("WOTW_UnityEngine_GetDeltaTimeHook, !bOnce");

	// 1/63 = 0.0158730f
	// 1/60 = 0.0166667f
	return SchixtySeven;
}

void * __fastcall il2cpp_runtime_invoke_Hook(MethodInfo* pMethodInfo, void* obj, void ** params, void ** exc)
{
	DoOnceBlock("il2cpp_runtime_invoke_Hook, !bOnce");
	static bool bHookedPlayerInputFixedUpdate = false;

	if (!bHookedPlayerInputFixedUpdate)
	{
		std::string className = pMethodInfo->pClass->pcszClassName;
		std::string methodName = pMethodInfo->pcszMethodName;

		if (className == "PlayerInput" && methodName == "FixedUpdate")
		{
			*(unsigned long long*)(&original_PlayerInputFixedUpdate) = pMethodInfo->methodAddr;
			PlayerInput_FixedUpdate_VA = pMethodInfo->methodAddr;
			pMethodInfo->methodAddr = (unsigned long long)PlayerInput_FixedUpdate_Hook;
			DebugOutput("Replaced pMethodInfo->methodAddr with PlayerInput_FixedUpdate_Hook.");
			bHookedPlayerInputFixedUpdate = true;
	
		}
	}

	return original_il2cpp_runtime_invoke(pMethodInfo, obj, params, exc);
}

void __fastcall WOTW_UnityEngine_PlayerLoopInternal_Hook()
{
	DoOnceBlock("WOTW_UnityEngine_PlayerLoopInternal_Hook, !bOnce");
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
	

	if (g_bPaused)
	{
		// VK_OEM_4 = '['
		// VK_OEM_6 = ']'

		if (GetAsyncKeyState(VK_OEM_4) & 1)
		{
			g_bPressedFrameStepThisFrame = true;
			original_WOTW_UnityEngine_PlayerLoopInternal();
		}

		return;
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

	static bool bGotCommandProcessors = false;

	if (!bGotCommandProcessors)
	{
		g_pButtonA = original_InputButtonProcessor_GetButton(EButton::ButtonA);
		g_pButtonB = original_InputButtonProcessor_GetButton(EButton::ButtonB);
		g_pButtonX = original_InputButtonProcessor_GetButton(EButton::ButtonX);
		g_pButtonY = original_InputButtonProcessor_GetButton(EButton::ButtonY);
		g_pPause = original_InputButtonProcessor_GetCommand(ECommand::OpenPauseScreen);
		g_pGrab = original_InputButtonProcessor_GetCommand(ECommand::Grab);
		g_pGrapple = original_InputButtonProcessor_GetCommand(ECommand::Grapple);
		g_pMenuClose = original_InputButtonProcessor_GetCommand(ECommand::MenuClose);
		g_pMenuSelect = original_InputButtonProcessor_GetCommand(ECommand::MenuSelect);
		g_pBash = original_InputButtonProcessor_GetCommand(ECommand::Bash);
		g_pBurrow = original_InputButtonProcessor_GetCommand(ECommand::Burrow);
		g_pGlide = original_InputButtonProcessor_GetCommand(ECommand::Glide);
		g_pAbilityWheel = original_InputButtonProcessor_GetCommand(ECommand::OpenWeaponWheel);
		g_pJump = original_InputButtonProcessor_GetCommand(ECommand::Jump);//original_InputButtonProcessor_GetButton(EButton::ButtonA);
		g_pDash = original_InputButtonProcessor_GetCommand(ECommand::Dash);//original_InputButtonProcessor_GetButton(EButton::LeftShoulder);

		// X Y B = Ability1,2,3
		g_pAbility1 = original_InputButtonProcessor_GetCommand(ECommand::Ability1);//original_InputButtonProcessor_GetButton(EButton::ButtonX);
		g_pAbility2 = original_InputButtonProcessor_GetCommand(ECommand::Ability2);//original_InputButtonProcessor_GetButton(EButton::ButtonY);
		g_pAbility3 = original_InputButtonProcessor_GetCommand(ECommand::Ability3);//original_InputButtonProcessor_GetButton(EButton::ButtonB);

		bGotCommandProcessors = true;
	}

	
	if (!pPlayerInput->m_bActive)
		return;


	// wut? lol
	if (!g_pPlaybackManager)
		return original_PlayerInputFixedUpdate(__rcx);


	Core_Input * pCoreInput = GetCoreInputInstance();
	// COME ON, MAN.
	g_pCoreInput = pCoreInput;

	// we ain't playing back, kick cans kid
	if (!g_pPlaybackManager->IsPlayingBack())
	{
		// For printing crap when we aren't playing back
		g_pPlaybackManager->FormatWithoutPlayback();
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
	pCoreInput->CursorPosition.m_fX = viewportPoint.x;
	pCoreInput->CursorPosition.m_fY = viewportPoint.y;

	if (g_pPlaybackManager->IsPlayingBack())
	{
		g_pPlaybackManager->DoPlayback(g_bPressedFrameStepThisFrame);
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

void ApplyPatch(unsigned long long addr, const char * bytes)
{
	unsigned int len = sizeof(bytes) / sizeof(bytes[0]);
	unsigned long dwOldProt = 0x0;

	VirtualProtect((LPVOID)addr, len, PAGE_EXECUTE_READWRITE, &dwOldProt);

	for (unsigned int i = 0; i < len; i++)
		*(unsigned char*)(addr + i) = bytes[i];

}
