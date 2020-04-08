#pragma once

#include "CharacterVisuals.h"
#include "CharacterPlatformMovement.h"

#pragma pack(push, 1)
class PlatformBehaviour
{
public:
	// 0x00 - 0x17
	unsigned char uc_Unk0000_0017[0x18];

	// 0x18 - 0x1F
	CharacterPlatformMovement * pPlatformMovement;

	// 0x20 - 0x77
	unsigned char uc_Unk0020_0077[0x78 - 0x20];

	// 0x78 - 0x7F
	CharacterVisuals * m_pVisuals;

	// 0x80 ---
};

#pragma pack(pop)