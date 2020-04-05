#pragma once

#include "AbilityType.h"
#define GAMEASSEMBLY_RESTRICTABILITYCONTROLLER_ISABILITYRESTRICTED_RVA 0x98ADC0

enum SeinAbilityRestrictZoneMask : unsigned long
{

	NoneZoneMask = 0,

	AnyZoneMask = 1,

	AttackZoneMask = 2,

	DashZoneMask = 4,

	JumpZoneMask = 8,

	SwordZoneMask = 16,

	DoubleJumpZoneMask = 32,

	TripleJumpZoneMask = 64,

	SpiritLeashZoneMask = 128,

	ButtonXZoneMask = 256,

	ButtonYZoneMask = 512,

	ButtonBZoneMask = 1024,

	BashZoneMask = 2048,

	GranadeZoneMask = 4096,

	HammerZoneMask = 8192,

	BowZoneMask = 16384,

	GlideZoneMask = 32768,

	LeafAttackZoneMask = 65536,

	WallJumpZoneMask = 131072,

	ChainswordZoneMask = 262144,

	InteractZoneMask = 524288,

	ChargeJumpZoneMask = 1048576,

	EquipmentWheelZoneMask = 2097152
};

typedef bool(__fastcall * fnRestrictAbilityController_IsRestricted)(AbilityType, SeinAbilityRestrictZoneMask);
extern fnRestrictAbilityController_IsRestricted RestrictAbilityController_IsRestricted;