#pragma once

#include "InputButtonProcessorTypedefs.h"

//.data:00007FFFD920F260 gameassembly.dll:$43DF260 #0
#define GAMEASSEMBLY_CMDINSTANCE_PTR_RVA 0x43DF260
#pragma pack(push, 1)

class Cmd
{
public:

	// 0x00 - 0x07
	InputButtonProcessor * AnyStart;
	
	// 0x08 - 0xF
	InputButtonProcessor * Down;

	// 0x10 - 0x17
	InputButtonProcessor * Up;

	// 0x18 - 0x1F
	InputButtonProcessor * Left;

	// 0x20 - 0x27
	InputButtonProcessor * Right;

	// 0x28 - 0x2F
	InputButtonProcessor * LeftClick;

	// 0x30 - 0x37
	InputButtonProcessor * RightClick;

	// 0x38 - 0x3F
	InputButtonProcessor * KeyboardOnly;

	// 0x40 - 0x47
	InputButtonProcessor * Unassigned;

	// 0x48 - 0x4F
	InputButtonProcessor * MainMenuSaveCopy;

	// 0x50 - 0x57
	InputButtonProcessor * MainMenuSaveDelete;

	// 0x58 - 0x5F
	InputButtonProcessor * Interact;

	// 0x60 - 0x67
	InputButtonProcessor * Jump;

	// 0x68 - 0x6F
	InputButtonProcessor * Ability1;

	// 0x70 - 0x77
	InputButtonProcessor * Ability2;

	// 0x78 - 0x7F
	InputButtonProcessor * Ability3;

	// 0x80 - 0x87
	InputButtonProcessor * Glide;

	// 0x88 - 0x8F
	InputButtonProcessor * Grab;

	// 0x90 - 0x97
	InputButtonProcessor * Dash;

	// 0x98 - 0x9F
	InputButtonProcessor * Burrow;

	// 0xA0 - 0xA7
	InputButtonProcessor * Bash;

	// 0xA8 - 0xAF
	InputButtonProcessor * Grapple;

	// 0xB0 - 0xB7
	InputButtonProcessor * DialogueAdvance;

	// 0xB8 - 0xBF
	InputButtonProcessor * DialogueOption1;

	// 0xC0 - 0xC7
	InputButtonProcessor * DialogueOption2;

	// 0xC8 - 0xCF
	InputButtonProcessor * DialogueOption3;

	// 0xD0 - 0xD7
	InputButtonProcessor * DialogueExit;

	// 0xD8 - 0xDF
	InputButtonProcessor * OpenMapShardsInventory;

	// 0xE0 - 0xE7
	InputButtonProcessor * OpenInventory;

	// 0xE8 - 0xEF
	InputButtonProcessor * OpenWorldMap;

	// 0xF0 - 0xF7
	InputButtonProcessor * OpenAreaMap;

	// 0xF8 - 0xFF
	InputButtonProcessor * OpenShards;

	// 0x100 - 0x107
	InputButtonProcessor * OpenWeaponWheel;

	// 0x108 - 0x10F
	InputButtonProcessor * OpenPauseScreen;

	// 0x110 - 0x117
	InputButtonProcessor * OpenLiveSignIn;

	// 0x118 - 0x11F
	InputButtonProcessor * MapZoomIn;

	// 0x120 - 0x127
	InputButtonProcessor * MapZoomOut;

	// 0x128 - 0x12F
	InputButtonProcessor * MenuSelect;

	// 0x130 - 0x137
	InputButtonProcessor * MenuBack;

	// 0x138 - 0x13F
	InputButtonProcessor * MenuClose;

	// 0x140 - 0x147
	InputButtonProcessor * MenuDown;

	// 0x148 - 0x14F
	InputButtonProcessor * MenuUp;

	// 0x150 - 0x157
	InputButtonProcessor * MenuLeft;

	// 0x158 - 0x15F
	InputButtonProcessor * MenuRight;

	// 0x160 - 0x167
	InputButtonProcessor * MenuPageLeft;

	// 0x168 - 0x16F
	InputButtonProcessor * MenuPageRight;

	// 0x170 - 0x177
	InputButtonProcessor * LeaderboardCycleFilter;

	// 0x178 - 0x17F
	InputButtonProcessor * MapFilter;

	// 0x180 - 0x187
	InputButtonProcessor * MapDetails;

	// 0x188 - 0x18F
	InputButtonProcessor * MapFocusOri;

	// 0x190 - 0x197
	InputButtonProcessor * MapFocusObjective;

	// 0x198 - 0x19F
	InputButtonProcessor * LiveSignIn;
protected:
private:
};
#pragma pack(pop)

extern unsigned long long gqw_CmdInstancePtr;

extern inline Cmd * GetCmdInstance();