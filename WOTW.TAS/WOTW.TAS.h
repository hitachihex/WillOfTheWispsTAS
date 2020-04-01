#pragma once
#include "stdafx.h"
#include <easyhook.h>
#include "IL2CPPDefs.h"
#include "PlaybackManager.h"
#include "PlayerInputTypeDefs.h"
#include "WOTW_Characters.h"
#include "GameSettings.h"
#include "QualitySettings.h"
#include "Utils.h"
#include "Vector3.h"
#include "InstantLoadScenesController.h"
#include "GameController.h"
#include "ScenesManager.h"
#include "UnityPlayer.h"
#include <Xinput.h>

extern unsigned long g_ACLEntries[1];
#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING

#define LODWORD(_qw)    ((DWORD)(_qw))

#define ExclusiveHookWithCount(a,b) MakeHookExclusive(g_ACLEntries, a, b)
#define ExclusiveHook(b) MakeHookExclusive(g_ACLEntries, 1, b)
#define DoOnceBlock(s) static bool bOnce=false; if(!bOnce) {  bOnce=true; DebugOutput(s); }

typedef unsigned long(WINAPI * oXInputGetState)(unsigned long, XINPUT_STATE*);
extern oXInputGetState original_XInputGetState;
extern unsigned long WINAPI XInputGetState_Hook(unsigned long, XINPUT_STATE*);
typedef void*(__fastcall * oil2cpp_runtime_invoke)(MethodInfo*, void*, void**, void**);
extern oil2cpp_runtime_invoke original_il2cpp_runtime_invoke;

typedef void(__fastcall * oPlayerInput_FixedUpdate)(unsigned long long);
extern oPlayerInput_FixedUpdate original_PlayerInputFixedUpdate;
extern void __fastcall PlayerInput_FixedUpdate_Hook(unsigned long long);

typedef void(__fastcall * oGameController_FixedUpdate)(unsigned long long);
extern oGameController_FixedUpdate original_GameControllerFixedUpdate;
extern void __fastcall GameController_FixedUpdate_Hook(unsigned long long);


extern void * __fastcall il2cpp_runtime_invoke_Hook(MethodInfo*, void*, void**, void**);

extern HOOK_TRACE_INFO WOTW_UnityEngine_GetDeltaTime_HookHandle;
extern HOOK_TRACE_INFO WOTW_UnityEngine_PlayerLoopInternal_HookHandle;
extern HOOK_TRACE_INFO WOTW_CompoundButtonInput_GetButton_HookHandle;

typedef void(__fastcall * oWOTW_UnityEngine_PlayerLoopInternal)();
extern oWOTW_UnityEngine_PlayerLoopInternal original_WOTW_UnityEngine_PlayerLoopInternal;

typedef float(__fastcall * oWOTW_UnityEngine_GeltaDeltaTime)();
extern oWOTW_UnityEngine_GeltaDeltaTime original_WOTW_UnityEngine_GetDeltaTime;
extern float __fastcall WOTW_UnityEngine_GetDeltaTime_Hook();
extern void __fastcall WOTW_UnityEngine_PlayerLoopInternal_Hook();

typedef bool(__fastcall * oCompoundButtonInput_GetButton)(unsigned long long);
extern oCompoundButtonInput_GetButton original_CompoundButton_GetButton;

extern bool __fastcall CompoundButton_GetButton_Hook(unsigned long long);

typedef InputButtonProcessor*(__fastcall * oInputButtonProcessor_GetButton)(unsigned int);
extern oInputButtonProcessor_GetButton original_InputButtonProcessor_GetButton;

typedef InputButtonProcessor*(__fastcall * oInputButtonProcessor_GetCommand)(unsigned int);
extern oInputButtonProcessor_GetCommand original_InputButtonProcessor_GetCommand;

typedef void(__fastcall * oUnityEngine_GetMousePositionInjected)(Vector3*);
extern oUnityEngine_GetMousePositionInjected original_UnityEngine_GetMousePositonInjected;

typedef void(__fastcall * fnScreenToViewportPoint_Injected)(UnityEngine_Camera*,Vector3*, Vector3*);
extern fnScreenToViewportPoint_Injected ScreenToViewportPoint_Injected;

typedef void(__fastcall * oPlayerInput_RefreshControls)(unsigned long long);
extern oPlayerInput_RefreshControls orig_PlayerInput_RefreshControls;

extern unsigned long long PlayerInput_FixedUpdate_VA;

extern void DumpPointersForExternalOSD();
extern void ApplyNops(unsigned long long,unsigned int);
extern void ApplyPatch(unsigned long long, const char*);


