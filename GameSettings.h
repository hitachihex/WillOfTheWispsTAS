#pragma once

extern unsigned long long gqw_GameSettingsInstance_Ptr;
#pragma pack(push, 1)

enum EControlScheme : unsigned int
{
	Controller,
	KeyboardAndMouse,
	Keyboard,
	Switch
};

typedef struct t_GameSettings
{

public:
	// 0x00 - 0x5B
	unsigned char uc_Unk[0x5C];

	// 0x5C - 0x5F
	EControlScheme m_CurrentControlScheme;
} GameSettings;

extern inline GameSettings * GetGameSettingsInstance();
#pragma pack(pop)