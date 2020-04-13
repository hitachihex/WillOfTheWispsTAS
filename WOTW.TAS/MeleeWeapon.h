#pragma once
#include "NullableType.h"
#include "ArrayWrapper.h"
#include "AbilityType.h"
#include "MoonEnums.h"
#include "UnityAnimator.h"
#include "MoonAnimator.h"
#include "MonoBehaviour.h"

#pragma pack(push, 1)

class SeinCharacter;

typedef struct t_TrackingExclusions
{
public:

	// 0x0000
	bool ExcludePosition;

	// 0x0001
	bool ExcludeRotation;

	// 0x0002
	bool ExcludeScale;

	// 0x0003
	bool ExcludeActivation;
protected:
private:
} TrackingExclusions;

class MeleeWeapon : public MonoBehaviour
{
public:

	// 0x0000 - 0x0017 - MonoBehaviour members

	// 0x0018
	bool DebugWeaponOutput;

	// 0x0019
	bool m_b0019;

	// 0x001A
	bool m_b001A;

	// 0x001B
	bool m_b001B;

	// 0x001C
	bool m_b001C;

	// 0x001D
	bool m_b001D;

	// 0x001E
	bool m_b001E;

	// 0x001F
	bool m_b001F;

	// 0x0020 - 0x0027
	unsigned long long DynamicDataResolver_m_dataResolver;

	// 0x0028 - 0x002F
	unsigned long long MeleeComboTransition_Transitions;

	// 0x0030 - 0x0037
	MoonAnimator * m_pAnimator;

	// 0x0038 - 0x003F
	MoonAnimator * m_pHeroAnimatorPreview;

	// 0x0040 - 0x0047
	UnityAnimator * m_pLegacyWeaponAnimator;

	// 0x0048 - 0x004F
	Moon::WeaponJoint m_weaponJoint;

	// 0x0050 - 0x0057
	unsigned long long Transform_m_targetJoint;

	// 0x0058 - 0x005F
	unsigned long long Transform_WeaponRoot;

	// 0x0060 - 0x0067
	unsigned long long MoonTimeline_m_allTimelines;

	// 0x0068 - 0x006F
	unsigned long long Transform_m_animatorTransforms;

	// 0x0070 - 0x0077
	SeinCharacter * m_pWeaponOwner;

	// 0x0078
	AbilityType AbilityType;

	// 0x0079
	bool m_b0079;

	// 0x007A
	bool m_b007A;

	// 0x007B
	bool m_b007B;

	// 0x007C - 0x007F
	unsigned long DamageLayerMask_DamageLayerMask;

	// 0x0080 - 0x0087
	unsigned long long DamageOwner_DamageOwner;

	// 0x0088 - 0x008F
	unsigned long long UpgradableMultiplier_Upgradable;

	// 0x0090 - 0x0097
	unsigned long long SerializedByteUberState_UpgradeLevel;

	// 0x0098 - 0x009F
	ArrayWrapper<float> *UpgradeEffectiveness;

	// 0x00A0
	bool InterruptComboOnDamageTaken;

	// 0x00A1
	bool InterruptComboOnDamageBlocked;

	// 0x00A2
	bool m_b00A2;

	// 0x00A3
	bool m_b00A3;

	// 0x00A4 - 0x00A7
	float InterruptComboMinRange;

	// 0x00A8 - 0x00AF
	unsigned long long MoonAnimation_GroundBlockAnimation;

	// 0x00B0 - 0x00B7
	unsigned long long AnimationCurve_GroundBlockKickbackCurve;

	// 0x00B8 - 0x00BF
	unsigned long long MoonAnimation_AirBlockAnimation;

	// 0x00C0 - 0x00C7
	unsigned long long AnimationCurve_AirBlockKickbackCurve;

	// 0x00C8
	bool FlattenKickbackDirection;

	// 0x00C9
	bool IgnoreTargetsBehind;

	// 0x00CA
	bool m_b00CA;

	// 0x00CB
	bool m_b00CB;

	// 0x00CC
	bool m_b00CC;

	// 0x00CD
	bool m_b00CD;

	// 0x00CE
	bool m_b00CE;

	// 0x00CF
	bool m_b00CF;

	// 0x00D0 - 0x00D7
	unsigned long long MaterialBasedSeinEffectsMap_HitEffects;

	// 0x00D8 - 0x00DF
	Vector2 GravityMultiplierRange;

	// 0x00E0 - 0x00E3
	float GravityMultiplierIncreaseSpeed;

	// 0x00E4 - 0x00E7
	float CurrentGravityMultiplier;

	// 0x00E8 - 0x00EF
	unsigned long long ActionDamageResult_DamageResultReceived;

	// 0x00F0 - 0x00F1
	NullableType<bool> m_attackButtonPressedCached;

	// 0x00F2
	bool IsPerformingCombo;

	// 0x00F3
	bool m_b00F3;

	// 0x00F4
	bool m_b00F4;

	// 0x00F5
	bool m_b00F5;

	// 0x00F6
	bool m_b00F6;

	// 0x00F7
	bool m_b00F7;

	// 0x00F8 - 0x00FF
	unsigned long long SeinComboHandler_ComboHandler;

	// 0x0100 
	bool m_canDeactivateRoot;

	// 0x0101
	bool m_isInitialized;
	
	// 0x0102
	bool m_spriteMirrorLock;

	// 0x0103
	bool m_b0103;

	// 0x0104
	bool m_b0104;

	// 0x0105
	bool m_b0105;

	// 0x0106
	bool m_b0106;

	// 0x0107
	bool m_b0107;

	// 0x0108 - 0x010F
	unsigned long long SoundHost_m_soundHost;

	// 0x0110 - 0x0113
	float WeaponCooldown;

	// 0x0114 - 0x0117
	float ProviderCooldown;

	// 0x0118 - 0x011F
	TrackingExclusions * m_pTrackingExclusions;
protected:
private:
};
#pragma pack(pop)