#pragma once

#define GAMECONTROLLER_RESETSTATISTICS_NEWPATCH_RVA 0x51BC70
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