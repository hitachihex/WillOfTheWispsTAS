#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <easyhook.h>
#include "EverythingNeedsMe.h"
#include "CharacterState.h"


#define SEINDASHNEW_GETCANDASH_RVA 0x81A2F0
#define SEINDASHNEW_ONPROCESSROOTMOTION_RVA 0x821AD0

extern HOOK_TRACE_INFO SeinDashNew_OnProcessRootMotion_HookHandle;
#pragma pack(push, 1)


class SeinDashNew : public CharacterState
{
public:
	// 0x00 - 0x7F = CharacterState members

	// 0x80
	bool m_bWasGroundedSinceLastExecution;

	// 0x81
	bool m_b0081;

	// 0x82
	bool m_b0082;

	// 0x83
	bool m_b0083;

	// 0x84 - 0x87
	unsigned int SandZoneHittingLayer;

	// 0x88 - 0x8B
	unsigned int WaterZoneHittingLayer;

	// 0x8C
	bool IsEnding;

	// 0x8D
	bool m_b008D;

	// 0x8E
	bool m_b008E;

	// 0x8F
	bool m_b008F;

	// 0x90 - 0x97
	unsigned long long PreDashDelegate;

	// 0x98
	bool OnlyRootMotion;

	// 0x99
	bool AllowAirDash;

	// 0x9A
	bool BackdashEnabled;

	// 0x9B
	bool ScaleForwardMotionToEnemies;

	// 0x9C - 0x9F
	float ForwardMotionDistance;

	// 0xA0 - 0xA3
	float ForwardAirMotionDistance;

	// 0xA4 - 0xA7
	unsigned int EnemyLayerMask;

	// 0xA8 - 0xAF
	unsigned long long LIST_STRING__RootMotionScalingIgnoreTags;

	// 0xB0 - 0xB3
	float ForwardStickThreshold;

	// 0xB4
	bool m_b00B4;

	// 0xB5
	bool m_b00B5;

	// 0xB6
	bool m_b00B6;

	// 0xB7
	bool m_b00B7;

	// 0xB8 - 0xBF
	unsigned long long AnimationCurve_MaxSpeedCurve;

	// 0xC0 - 0xC3
	float AllowMeleeAttackNormalizedTime;

	// 0xC4 - 0xC7
	float StuckOnWallDuration;

	// 0xC8 - 0xCB
	float InvincibilityToAttacksTime;

	// 0xCC - 0xCF
	float PostDashSpeed;

	// 0xD0 - 0xD3
	float DigTolerance;

	// 0xD4
	bool m_b00D4;

	// 0xD5
	bool m_b00D5;

	// 0xD6
	bool m_b00D6;

	// 0xD7
	bool m_b00D7;

	// 0xD8 - 0xDF
	unsigned long long GameObject_DashEntryTarget;

	// 0xE0 - 0xE7
	unsigned long long MoonTimeline_ActivateDiggingTargetSequence;

	// 0xE8 - 0xEF
	unsigned long long MoonTimeline_DeactivateDiggingTargetSequence;

	// 0xF0 - 0xF3
	float Cooldown;

	// 0xF4 - 0xF7
	float ProviderCooldownTimer;

	// 0xF8 - 0xFB
	float m_timeToGetUnstuck;

	// 0xFC - 0xFF
	float m_currentDistanceTravelled;

	// 0x100 - 0x103
	float m_predictedTravelDistance;

	// 0x104 - 0x107
	float m_rootMotionScale;

	// 0x108
	bool m_isDashing;

	// 0x109
	bool m_isAirDashing;

	// 0x10A
	bool m_allowDash;

	// 0x10B
	bool m_attackButtonPressedDuringDash;

	// 0x10C
	bool m_forwardDash;

	// 0x10D
	bool m_b0010D;

	// 0x10E
	bool m_b0010E;

	// 0x10F
	bool m_b0010F;

	// 0x110 - 0x113
	int m_dashDirection;

	// 0x114 - 0x117
	int m_facingDirection;

	// 0x118 - 0x11F
	unsigned long long MoonTimeline_m_currentTimeline;

	// 0x120 - 0x127
	unsigned long long MoonAnimator_m_seinAnimator;

	// 0x128 - 0x12F
	Vector2 m_previousPosition;

	// 0x130 - 0x13B
	// dump says v2, but this is 4*3
	Vector3 m_dashEntryPoint;

	// 0x13C - 0x143
	Vector2 m_dashEntryPointNormal;

	// 0x144 - 0x14F
	Vector3 m_adjustedDashDirection;

	// 0x150 - 0x157
	unsigned long long LIST_DIGZONE_m_digZonesWithinRadius;

	// 0x158 - 0x15F
	unsigned long long LIST_WATERZONE_m_swimZonesWithinRadius;

	// 0x160 - 0x167
	unsigned long long DigZone_m_targetDigZone;

	// 0x168 - 0x16F
	unsigned long long Rigidbody_m_targetDigZoneRigidbody;

	// 0x170 - 0x177
	unsigned long long WaterZone_m_targetWaterZone;

	// 0x178 - 0x17B
	float DigDirectionErrorAngle;
	
	// 0x17C - 0x17F
	float DistanceCostMultiplier;

	// 0x180 - 0x183
	float AngleCostMultiplier;

	// 0x184 - 0x187
	float InputDirectionOffsetY;

	// 0x188 - 0X18B
	float MoveCooldown;

	// 0x18C - 0x18F
	float MoveCooldownTimer;

	// 0x190 - 0x197
	unsigned long long IComboMove_Array_ComboMoves;

	// 0x198 - 0x1A3
	Vector3 m_lastRootVelocity;


	// ---------- methods
	void UpdateDash();

	float GetRootMotionScale(float);
protected:
private:

};
#pragma pack(pop)

typedef bool(__fastcall * fnSeinDashNew_CanDash)(SeinDashNew*);
typedef void(__fastcall * fnSeinDashNew_OnProcessRootMotion)(SeinDashNew*, Vector3*);
extern fnSeinDashNew_OnProcessRootMotion original_SeinDashNew_OnProcessRootMotion;

extern fnSeinDashNew_CanDash SeinDashNew_CanDash;
extern void __fastcall SeinDashNew_OnProcessRootMotion_Hook(SeinDashNew*, Vector3*);
