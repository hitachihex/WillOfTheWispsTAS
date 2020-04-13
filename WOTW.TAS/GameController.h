#pragma once

#include "SaveGameController.h"

#define GAMECONTROLLER_RESETSTATISTICS_NEWPATCH_RVA 0x498FA0
#define GAMECONTROLLERINSTANCE_OFFSET_TO_PTR        0x87
#define GAMECONTROLLER_RESTORECHECKPOINTIMMEDIATE_RVA 0x4A26C0
#pragma pack(push, 1)
class GameController
{
public:
	// 0x0000 - 0x0037
	unsigned char uc_Unk0000_0037[0x38];

	// 0x0038 - 0x003F
	SaveGameController * m_pSaveGameController;

	// 0x0040 - 0x010A
	unsigned char uc_Unk0040_010A[0x10B - 0x40];

	// 0x10B
	bool m_bIsLoadingGame;

protected:
private:
};

#pragma pack(pop)

extern unsigned long long gqw_GameControllerInstancePtr;
extern GameController * g_pGameControllerInstance;

extern inline GameController * GetGameControllerInstance();

//typedef void(__fastcall * oPlayerInput_FixedUpdate)(unsigned long long);
typedef void(__fastcall * oGameController_OnGUI)();
extern oGameController_OnGUI orig_GameController_OnGUI;
extern void __fastcall GameController_OnGUI_Hook();

extern void __fastcall MyWindow_Delegate(int);
