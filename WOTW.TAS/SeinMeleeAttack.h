#pragma once

#include "Vector2.h"
#include "UnityAnimator.h"
#include "GameObject.h"
#include "MeleeWeapon.h"
#include "CharacterState.h"

#pragma pack(push, 1)

class SeinMeleeAttack : public CharacterState
{
public:

	// 0x0000 - 0x007F - CharacterState members

	// 0x0080 - 0x0087
	GameObject * m_pWeaponPrefabs;

	// 0x0088 - 0x008F
	unsigned long long MeleeWeapon_Weapons;

	// 0x0090 - 0x0093
	float CooldownAfterDamageTaken;

	// 0x0094
	bool DisableRootMotionWhenNearEnemy;

	// 0x0095
	bool m_b0095;

	// 0x0096
	bool m_b0096;

	// 0x0097
	bool m_b0097;

	// 0x0098 - 0x009B
	float DisableRootMotionRadius;

	// 0x009C - 0x009F
	unsigned long LayerMask_DisableRootMotionCollisionMask;

	// 0x00A0 - 0x00A3
	float HighlightRange;

	// 0x00A4 - 0x00A7
	float DamageBlockedCooldown;

	// 0x00A8 - 0x00AB
	float DamageBlockedInputLockDuration;

	// 0x00AC - 0x00AF
	unsigned long m_dwUnk00AC_00AF;

	// 0x00B0 - 0x00B7
	unsigned long long Kickback_DamageBlockedKickback;

	// 0x00B8 - 0x00BF
	UnityAnimator * m_pSeinAnimator;

	// 0x00C0 - 0x00C7
	unsigned long long Transform_m_weaponJoint;

	// 0x00C8 - 0x00CF
	unsigned long long Transform_m_rootJoint;

	// 0x00D0 - 0x00D7
	unsigned long long CameraShake_m_cameraShake;

	// 0x00D8
	bool m_spriteMirrorLock;

	// 0x00D9
	bool m_unequipWeapon;

	// 0x00DA
	bool m_b00DA;

	// 0x00DB
	bool m_b00DB;

	// 0x00DC - 0x00DF
	float m_timeDamageTaken;

	// 0x00E0 - 0x00E3
	float m_comboCooldownTimeLeft;

	// 0x00E4 - 0x00E7
	float m_damageBlockedCooldownTimeLeft;

	// 0x00E8 - 0x00EF
	MeleeWeapon * m_pCurrentWeapon;

	// 0x00F0 - 0x00F7
	unsigned long long MeleeComboMove_m_currentComboMove;

	// 0x00F8 - 0x00FF
	unsigned long long DamageOwner_m_damageOwner;

	// 0x0100 - 0x0107
	unsigned long long ListActivateCooldownRule_m_currentCooldownRules;

	// 0x0108 - 0x010F
	Vector2 m_retainedRootMotion;

	// 0x0110 - 0x0117
	unsigned long long ListISpiritFlameAttackable_m_lastClosestAttackables;

	// 0x0118 - 0x011F
	unsigned long long ListISpiritFlameAttackable_m_closestAttackables;
protected:
private:

};
#pragma pack(pop)
