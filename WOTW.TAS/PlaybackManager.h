#pragma once

#include "InputRecord.h"
#include "InputButtonProcessorTypedefs.h"
#include <stdio.h>
#include <sstream>
#include <vector>
#include <string>
#include "Vector3.h"
#include "Core_Input.h"
#include "SeinCharacter.h"
#include "GameSettings.h"
#include "Addresses.h"
#include "UnityEngine_PhysicsSettings.h"
#include "Utils.h"
#include "GameController.h"
#include "InstantLoadScenesController.h"
#include "ScenesManager.h"
#include "UnityPlayer.h"
#include "FixedRandom.h"
#include "Cmd.h"


typedef Vector3*(__fastcall * fnSeinCharacter_GetPosition)(Vector3*, SeinCharacter*);
extern fnSeinCharacter_GetPosition SeinCharacter_GetPosition;

typedef void(__fastcall * fnSeinCharacter_SetPosition)(SeinCharacter*, Vector3*);
extern fnSeinCharacter_SetPosition SeinCharacter_SetPosition;

typedef Vector2*(__fastcall * fnSeinCharacter_GetLocalSpeed)(SeinCharacter*);
extern fnSeinCharacter_GetLocalSpeed SeinCharacter_GetLocalSpeed;

typedef Vector3*(__fastcall * fnCharPlatformMovement_GetRigidbodyVelocity)(Vector3*, CharacterPlatformMovement*);
extern fnCharPlatformMovement_GetRigidbodyVelocity CharPlatformMovement_GetRigidbodyVelocity;

typedef void(__fastcall * fnUnityEngine_SetTimeScale)(float);
extern fnUnityEngine_SetTimeScale UnityEngine_SetTimeScale;

typedef void(__fastcall * fnUnityEngine_SetVSyncCount)(unsigned int);
extern fnUnityEngine_SetVSyncCount UnityEngine_SetVSyncCount;

typedef void(__fastcall * fnUnityEngine_SetMaximumDeltaTime)(float);
extern fnUnityEngine_SetMaximumDeltaTime UnityEngine_SetMaximumDeltaTime;

extern unsigned long long *gp_qwUnityEngineTargetFrameRatePtr;
extern unsigned long long g_qwPlayerInputInstance;
extern bool g_bShowOSD;
extern bool g_bPaused;
extern bool g_bPressedFrameStepThisFrame;
//extern InputButtonProcessor * g_pUpProcessor, *g_pDownProcessor, *g_pLeftProcessor, *g_pRightProcessor;
extern Core_Input * g_pCoreInput;

extern InputButtonProcessor * g_pDash, *g_pJump, *g_pGrab, *g_pGlide, *g_pAbility1, *g_pAbility2, *g_pAbility3, *g_pButtonA, *g_pMenuSelect,
*g_pAbilityWheel, *g_pBurrow, *g_pBash, *g_pGrapple,*g_pPause, *g_pMenuClose, *g_pButtonB, *g_pButtonY, *g_pButtonX;
extern SeinCharacter * g_pSeinCharacter;
class PlaybackManager
{
public:

	PlaybackManager(const char*);

	InputRecord * GetCurrentInput();

	InputRecord * GetCurrentInputIndexBased();

	unsigned long GetCurrentInputIndex();

	unsigned long ReloadPlayback();

	bool ReadInputFile();

	void InitPlayback(bool);

	bool IsPlayingBack();

	unsigned long GetTotalFrameCount();

	void DoPlayback(bool, Vector2*);

	unsigned long GetCurrentSeed();

	XINPUT_STATE * GetXInputState();

	void SetFrameRate(unsigned int, bool, float);

	void FormatConditonally();

	void FormatWithPlayback();

	void FormatWithoutPlayback();

	std::string m_CWD;

	bool IsGameLoading();

#pragma region publicForOSD
	InputRecord * m_pCurrentInput;

	unsigned int CurrentFrameRate;

	unsigned long m_CurrentFrame;

	unsigned long m_nTotalFrameCount;

	bool m_bPlayingBack;

	char m_szCurrentManagerState[800];

	bool m_bLoading;

	unsigned long m_CurrentSeed;

	void CopyCursorPosition();
	void CopyPlayerPosition();
	void CopyPlayerSpeed();
	void CopyToClipboard(std::string);
#pragma endregion

	unsigned int m_RuntoFramerate;

	float m_fRuntoTimescale;
protected:
private:
	const char * m_szDefaultFileName = "Ori.rec";

	unsigned long m_nCurrentSeed;

	std::vector<InputRecord*> m_Inputs;

	unsigned long m_InputIndex;

	FILE * m_Fp;

	/* Do we only need to handle this during dashes?
	   Thinking, set Kinematic to true and do our thing.
	*/
	FILE * m_fpRigidbodyState;

	unsigned long long m_RuntoLineNo;

	unsigned long long m_WalktoLineNo;

	unsigned long m_FrameToNext;

	XINPUT_STATE * m_pGamePadState;

	char m_szCurrentDirectory[256];

	std::string m_CursorPos;
	std::string m_PlayerPos;
	std::string m_PlayerSpeed;
};

extern PlaybackManager * g_pPlaybackManager;