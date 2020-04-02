#pragma once

#pragma pack(push, 1)
typedef struct t_InputButtonProcessor
{
	
	inline void Update(bool bIsPressed)
	{
		this->m_bWasPressed = this->m_bIsPressed;
		this->m_bIsPressed = bIsPressed;
	}

	// 0x00 - 0x03
	unsigned long m_dwUnk00_03;

	// 0x04 - 0x07
	unsigned long m_dwUnk04_07;

	// 0x08 - 0x0B
	unsigned long m_dwUnk08_0B;

	// 0x0C - 0x0F
	unsigned long m_dwUnk0C_0F;

	// 0x10
	bool m_bWasPressed;

	// 0x11
	bool m_bIsPressed;

	// 0x12
	bool m_bUsed;

	// 0x13
	bool m_bUnk0013;

	// 0x14
	unsigned int m_ForcePressedFrames;

} InputButtonProcessor;

enum EButton : unsigned int
{

	ButtonA,

	ButtonX,

	ButtonY,

	ButtonB,

	LeftTrigger,

	RightTrigger,

	LeftShoulder,

	RightShoulder,

	Left,

	Right,

	Up,

	Down,

	Unassigned,

	Any,

	LeftStick,

	RightStick
};

enum ECommand : unsigned int
{

	Unassigned1,

	Jump,

	Interact,

	Ability1,

	Ability2,

	Ability3,

	Glide,

	Grab,

	Dash,

	Burrow,

	Bash,

	Grapple,

	DialogueAdvance,

	DialogueOption1,

	DialogueOption2,

	DialogueOption3,

	DialogueExit,

	OpenLastMapShardsInventory,

	OpenInventory,

	OpenWorldMap,

	OpenAreaMap,

	OpenShardsScreen,

	OpenWeaponWheel,

	OpenPauseScreen,

	OpenLiveSignIn,

	MenuSelect,

	MenuBack,

	MenuClose,

	MenuPageLeft,

	MenuPageRight,

	LeaderboardCycleFilter,

	MapZoomIn,

	MapZoomOut,

	MapFilter,

	MapDetails,

	MapFocusOri,

	MapFocusObjective,

	MainMenuSaveCopy,

	MainMenuSaveDelete
};


#pragma pack(pop)