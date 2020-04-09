#pragma once

#define GAMECONTROLLER_RESETSTATISTICS_NEWPATCH_RVA 0x498FA0
#define GAMECONTROLLERINSTANCE_OFFSET_TO_PTR        0x87
#pragma pack(push, 1)
typedef struct t_GameController
{

	// 0x0000 - 0x0010A
	unsigned char uc_Unk0000_0010A[0x10B];

	// 0x10B
	bool m_bIsLoadingGame;
} GameController;

#pragma pack(pop)

extern unsigned long long gqw_GameControllerInstancePtr;
extern GameController * g_pGameControllerInstance;

extern inline GameController * GetGameControllerInstance();

//typedef void(__fastcall * oPlayerInput_FixedUpdate)(unsigned long long);
typedef void(__fastcall * oGameController_OnGUI)();
extern oGameController_OnGUI orig_GameController_OnGUI;
extern void __fastcall GameController_OnGUI_Hook();