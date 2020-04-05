#pragma once


#include "CharacterStateWrapper.h"
#include "SeinWallJump.h"
#include "SeinDashNew.h"
#include "SeinJump.h"
#include "SeinDoubleJump.h"
#include "SeinChargeJump.h"
#include "RestrictAbilityController.h"
#pragma pack(push, 1)

class SeinAbilities
{
public:

	// 0x00 - 0x07
	unsigned long long m_qwUnk0000_0007;

	// 0x08 - 0x0F
	unsigned long long m_qwUnk0008_000F;

	// 0x10 - 0x17
	CharacterStateWrapper<SeinDoubleJump*> * DoubleJumpWrapper;

	// 0x18 - 0x1F
	CharacterStateWrapper<SeinJump*> *JumpWrapper;

	// 0x20 - 0x27
	// um, is this a pointer in here? or what
	CharacterStateWrapper<SeinWallJump*> * WallJumpWrapper;

	// 0x28 - 0x2F
	unsigned long long CharacterStateWrapper_SeinChargeJumpCharging_ChargeJumpChargingWrapper;

	// 0x30 - 0x37
	CharacterStateWrapper<SeinChargeJump*> * ChargeJumpWrapper;

	// 0x38 - 0x97
	unsigned char uc_Unk0038_0097[0x98 - 0x38];

	// 0x98 - 0x9F
	CharacterStateWrapper<SeinDashNew*> * DashNewWrapper;
protected:
private:
};
#pragma pack(pop)