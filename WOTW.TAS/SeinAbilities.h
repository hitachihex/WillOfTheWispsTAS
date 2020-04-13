#pragma once


#include "CharacterStateWrapper.h"
#include "SeinComboHandler.h"
#include "SeinMeleeAttack.h"
#include "SeinWallJump.h"
#include "SeinWallSlide.h"
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


	// 0x38 - 0x6F
	unsigned char uc_Unk0038_0097[0x70 - 0x38];

	// 0x70 - 0x77
	CharacterStateWrapper<SeinWallSlide*> * WallSlideWrapper;

	// 0x78 - 0x7F
	unsigned long long GrabRopeWrapper;

	// 0x80 - 0x87
	unsigned long long EdgeClamberWrapper;

	// 0x88 - 0x8F
	unsigned long long SwimmingWrapper;

	// 0x90 - 0x97
	unsigned long long DiggingWrapper;

	// 0x98 - 0x9F
	CharacterStateWrapper<SeinDashNew*> * DashNewWrapper;

	// 0xA0 - 0xA7
	unsigned long long DrillWrapper;

	// 0xA8 - 0xAF
	unsigned long long GoldenSeinWrapper;

	// 0xB0 - 0xB7
	unsigned long long FallWrapper;

	// 0xB8 - 0xBF
	unsigned long long RunWrapper;

	// 0xC0 - 0xC7
	unsigned long long IdleWrapper;

	// 0xC8 - 0xCF
	unsigned long long LookUpWrapper;

	// 0xD0 - 0xD7
	unsigned long long BashWrapper;

	// 0xD8 - 0xDF
	unsigned long long SpiritFlameWrapper;

	// 0xE0 - 0xE7
	unsigned long long StandardSpiritFlameWrapper;

	// 0xE8 - 0xEF
	unsigned long long CarryWrapper;

	// 0xF0 - 0xF7
	unsigned long long HoldWrapper;

	// 0xF8 - 0xFF
	unsigned long long InvincibilityWrapper;

	// 0x100 - 0x107
	unsigned long long PushAgainstWallWrapper;

	// 0x108 - 0x10F
	unsigned long long StandingOnEdgeWrapper;

	// 0x110 - 0x117
	unsigned long long LeverWrapper;

	// 0x118 - 0x11F
	unsigned long long FootstepsWrapper;

	// 0x120 - 0x127
	unsigned long long InteractionWrapper;

	// 0x128 - 0x12F
	unsigned long long CinematicWrapper;

	// 0x130 - 0x137
	unsigned long long CinematicToGameplayWrapper;

	// 0x138 - 0x13F
	unsigned long long SpiritFlameTargettingWrapper;

	// 0x140 - 0x147
	unsigned long long ChargeFlameWrapper;

	// 0x148 - 0x14F
	unsigned long long IceSpiritFlameWrapper;

	// 0x150 - 0x157
	unsigned long long DashWrapper;

	// 0x158 - 0x15F
	unsigned long long GrenadeWrapper;

	// 0x160 - 0x167
	unsigned long long TeleportWrapper;

	// 0x168 - 0x16F
	unsigned long long BounceWrapper;

	// 0x170 - 0x177
	unsigned long long SpiritLeashWrapper;

	// 0x178 - 0x17F
	unsigned long long SpirtSlashWrapper;

	// 0x180 - 0x187
	unsigned long long HeavySpiritSlashWrapper;

	// 0x188 - 0x18F
	unsigned long long BowWrapper;

	// 0x190 - 0x197
	CharacterStateWrapper<SeinMeleeAttack*> * MeleeWrapper;

	// 0x198 - 0x19F
	unsigned long long GrabSurfaceWrapper;

	// 0x1A0 - 0x1A7
	unsigned long long PinnedWrapper;

	// 0x1A8 - 0x1AF
	unsigned long long LeachedWrapper;

	// 0x1B0 - 0x1B7
	unsigned long long RideWrapper;

	// 0x1B8 - 0x1BF
	unsigned long long LaunchWrapper;

	// 0x1C0 - 0x1C7 - Combo stuff
	CharacterStateWrapper<SeinComboHandler*> * ComboWrapper;

	// 0x1C8 - 0x1CF
	unsigned long long SpiritMagnetWrapper;

	// 0x1D0 - 0x1D7
	unsigned long long SpiritSpearWrapper;
protected:
private:
};
#pragma pack(pop)