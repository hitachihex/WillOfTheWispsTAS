#pragma once
#include "CharacterState.h"

#define GAMEASSEMBLY_SEINCHARGEJUMP_CANCHARGE_RVA 0xA6CF00
#define GAMEASSEMBLY_SEINCHARGEJUMP_CANSTARTCHARGING_RVA 0xA6CEA0
#pragma pack(push, 1)

class SeinChargeJump : CharacterState
{
public:
	// 0x00 - 0x7F - CharacterState fields
	
	// 0x80 - 0x8F
	unsigned char uc_Unk0080_0017F[0x90 - 0x80];

	// 0x90
	bool WasGroundedSinceLastExecution;

	// 0x91
	bool m_b0091;

	// 0x92
	bool m_b0092;

	// 0x93
	bool m_b0093;

	// 0x0094 - 0x017F
	unsigned char uc_Unk0094_0017F[0x180 - 0x94];

	// 0x180
	bool m_CanChargeJump;

protected:
private:
};
#pragma pack(pop)
