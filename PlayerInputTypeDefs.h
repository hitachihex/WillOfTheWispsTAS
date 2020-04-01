#pragma once
#pragma pack(push, 1)

#include "CompoundButtonInput.h"

typedef struct t_PlayerInput
{
	// 0x00 - 0x03
	unsigned long m_dwUnk00_03;

	// 0x04 - 0x07
	unsigned long m_dwUnk04_07;

	// 0x08 - 0x0B
	unsigned long m_dwUnk08_0B;

	// 0x0C - 0x0F
	unsigned long m_dwUnk0C_0F;

	// 0x10 - 0x13
	unsigned long m_dwUnk0010_0013;

	// 0x14 - 0x17
	unsigned long m_dwUnk0014_0017;

	// 0x18
	bool m_bActive;

	// 0x19
	bool m_b0019;

	// 0x1A
	bool m_b001A;

	// 0x1B
	bool m_b001B;

	// 0x1C
	bool m_b001C;

	// 0x1D
	bool m_b001D;

	// 0x1E
	bool m_b001E;

	// 0x1F
	bool m_b001F;

	// 0x20 - 0x27
	unsigned long long HorizontalAnalogLeft;

	// 0x28 - 0x2F
	unsigned long long VerticalAnalogLeft;

	// 0x30 - 0x37
	unsigned long long HorizontalAnalogRight;

	// 0x38 - 0x3F
	unsigned long long VerticalAnalogRight;

	// 0x40 - 0x47
	unsigned long long HorizontalDigiPad;

	// 0x48 - 0x4F
	unsigned long long VerticalDigiPad;

	// 0x50 - 0x57
	unsigned long long LeftTriggerAxis;

	// 0x58 - 0x5F
	unsigned long long RightTriggerAxis;

	// 0x60 - 0x67
	CompoundButtonInput * p_Down;

	// 0x68 - 0x6F
	CompoundButtonInput * pUp;

	// 0x70 - 0x77
	CompoundButtonInput * pLeft;

	// 0x78 - 0x7F
	CompoundButtonInput * pRight;

	// 0x80 - 0x87
	CompoundButtonInput * pChargeJump;

	// 0x88 - 0x8F
	CompoundButtonInput * pLeftShoulder;

	// 0x90 - 0x97
	CompoundButtonInput * pRightShoulder;

	// 0x98 - 0x9F
	CompoundButtonInput * pLeftTrigger;

	// 0xA0 - 0xA7
	CompoundButtonInput * pRightTrigger;

	// 0xA8 - 0xAF
	CompoundButtonInput * pSelect;

	// 0xB0 - 0xB7
	CompoundButtonInput * pStart;

	// 0xB8 - 0xBF
	CompoundButtonInput * pLeftStick;

	// 0xC0 - 0xC7
	CompoundButtonInput * pRightStick;

	// 0xC8 - 0xCF
	CompoundButtonInput * pMenuCycleFilter;

	// 0xD0 - 0xD7
	CompoundButtonInput * pActionButtonA;

	// 0xD8 - 0xDF
	CompoundButtonInput * pActionButtonB;

	// 0xE0 - 0xE7
	CompoundButtonInput * pActionButtonX;

	// 0xE8 - 0xEF
	CompoundButtonInput * pActionButtonY;

	// 0xF0 - 0xF7
	CompoundButtonInput * pCancel;

	// 0xF8 - 0xFF
	CompoundButtonInput * pMainMenuSaveCopy;

	// 0x100 - 0x107
	CompoundButtonInput * pMainMenuSaveDelete;

	// 0x108 - 0x10F
	CompoundButtonInput * pFocus;

	// 0x110 - 0x117
	CompoundButtonInput * pLeaderboardDifficultyFilter;

	// 0x118 - 0x11F
	CompoundButtonInput * pLegend;

	// 0x120 - 0x127
	CompoundButtonInput * pPause;

	// 0x128 - 0x12F
	CompoundButtonInput * pKeyboardOnly;

	// 0x130 - 0x137
	CompoundButtonInput * pInteract;

	// 0x138 - 0x13F
	CompoundButtonInput * pJump;

	// 0x140 - 0x147
	CompoundButtonInput * pAbility1;

	// 0x148 - 0x14F
	CompoundButtonInput * pAbility2;

	// 0x150 - 0x157
	CompoundButtonInput * pAbility3;

	// 0x158 - 0x15F
	CompoundButtonInput * pGlide;

	// 0x160 - 0x167
	CompoundButtonInput * pGrab;

	// 0x168 - 0x16F
	CompoundButtonInput * pDash;

	// 0x170 - 0x177
	CompoundButtonInput * pBurrow;

	// 0x178 - 0x17F
	CompoundButtonInput * pBash;

	// 0x180 - 0x187
	CompoundButtonInput * pGrapple;

	// 0x188 - 0x18F
	CompoundButtonInput * pDialogueAdvance;

	// 0x190 - 0x197
	CompoundButtonInput * pDialogueOption1;

	// 0x198 - 0x19F
	CompoundButtonInput * pDialogueOption2;

	// 0x1A0 - 0x1A7
	CompoundButtonInput * pDialogueOption3;

	// 0x1A8 - 0x1AF
	CompoundButtonInput * pDialogueExit;

	// 0x1B0 - 0x1B7
	CompoundButtonInput * pOpenMapsShardsInventory;

	// 0x1B8 - 0x1BF
	CompoundButtonInput * pOpenInventory;

	// 0x1C0 - 0x1C7
	CompoundButtonInput * pOpenWorldMap;

	// 0x1C8 - 0x1CF
	CompoundButtonInput * pOpenAreaMap;

	// 0x1D0 - 0x1D7
	CompoundButtonInput * pOpenShards;

	// 0x1D8 - 0x1DF
	CompoundButtonInput * pOpenWeaponWheel;

	// 0x1E0 - 0x1E7
	CompoundButtonInput * pPauseScreen;

	// 0x1E8 - 0x1EF
	CompoundButtonInput * pLiveSignIn;

	// do rest later, this is boring

} PlayerInput;

#pragma pack(pop)


