#pragma once
#include "Vector3.h"
//#include "CharacterState.h"
#include "Rigidbody.h"
#include "SeinAbilities.h"
#include "IsOnCollisionState.h"
#include "CharacterVisuals.h"
#include "SeinLogicCycle.h"
//#include "RestrictAbilityController.h"
#include "EverythingNeedsMe.h"
#pragma pack(push, 1)


typedef struct t_CharacterPlatformMovement
{
	// local speed @ 0x80, let's just get that for now

public:
	
	// 0x00 - 0x1F
	unsigned char uc_Unk0000_007F[0x20];

	// 0x20 - 0x27
	IsOnCollisionState * m_pCeiling;

	// 0x28 - 0x2F
	IsOnCollisionState * m_pOnGround;

	// 0x30 - 0x37
	IsOnCollisionState * m_pWallLeft;

	// 0x38 - 0x3F
	IsOnCollisionState * m_pWallRight;

	// 0x40 - 0x4B
	Vector3 CeilingNormal;

	// 0x4C - 0x57
	Vector3 GroundNormal;

	// 0x58 - 0x63
	Vector3 WallRightNormal;

	// 0x64 - 0x6F
	Vector3 WallLeftNormal;

	// 0x70 - 0x73
	float fallTime;

	// 0x74 - 0x77
	float landTime;

	// 0x78 - 0x7B
	float ClimbableWallAngleLimit;

	// 0x7C - 0x7F
	float LastTimeOnGround;

	// 0x80 -  0x8B
	Vector3 m_LocalSpeed;

	// 0x8C - 0xCF
	unsigned char uc_Unk008C_00CF[0xD0 - 0x8C];

	// 0xD0 - 0xDB
	Vector3 m_PreviousPosition;

	// 0xDC
	bool m_b00DC;
	
	// 0xDD
	bool m_b00DD;

	// 0xDE
	bool m_b00DE;

	// 0xDF
	bool m_b00DF;

	// 0xE0 - 0xE7
	Rigidbody * m_pRigidbody;

	// 0xE8 - ??

} CharacterPlatformMovement;

typedef struct t_PlatformBehaviour
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
} PlatformBehaviour;

class SeinCharacter
{
public:


	// 0x00 - 0x17
	unsigned char uc_Unk0000_0017[0x18];

	// 0x18 - 0x1F
	SeinLogicCycle * m_pLogicCycle;

	// 0x20 - 0x27
	SeinAbilities * m_pAbilities;

	// 0x28 - 0x97
	unsigned char uc_Unk0028_0097[0x98 - 0x28];

	// 0x98 - 0x9F
	PlatformBehaviour * pPlatformBehaviour;

	
	// ----- inline methods
	inline bool IsOnWall()
	{
		float LocalSpeedX = this->pPlatformBehaviour->pPlatformMovement->m_LocalSpeed.x;

		if (LocalSpeedX < 0.0f)
			return this->pPlatformBehaviour->pPlatformMovement->m_pWallLeft->IsOn;

		return this->pPlatformBehaviour->pPlatformMovement->m_pWallRight->IsOn;

	}

	inline bool IsFalling()
	{
		CharacterPlatformMovement * pPlatformMovement = this->pPlatformBehaviour->pPlatformMovement;

		// that's interesting, does the game *actually* think we are falling when we're upslashing?
		// Maybe we should check for Rigidbody velocity too, but the game doesn't.
		return !pPlatformMovement->m_pOnGround->IsOn && pPlatformMovement->m_LocalSpeed.y < 0.0001f;

	}

	inline Rigidbody * GetRigidbody()
	{
		if (this->pPlatformBehaviour == nullptr)
			return nullptr;

		if (this->pPlatformBehaviour->pPlatformMovement == nullptr)
			return nullptr;

		return this->pPlatformBehaviour->pPlatformMovement->m_pRigidbody;
	}

	inline void SetRigidbodyPosition(float newX, float newY, float newZ, bool setPrevious = true)
	{
		auto pRb = this->GetRigidbody();

		if (pRb == nullptr)
			return;

		pRb->m_pInternalState->m_pInternal2->m_Position.Set(newX, newY, newZ);
		if (setPrevious)
			pRb->m_pInternalState->m_pInternal2->m_PrevPosition.Set(newX, newY, newZ);
	}

	inline void SetVelocity(float newX, float newY, float newZ, bool setPrevious = true)
	{
		auto pRb = this->GetRigidbody();

		if (pRb == nullptr)
			return;

		pRb->m_pInternalState->m_pInternal2->m_Velocity.Set(newX, newY, newZ);

		// if(setPrevious)
	}

	inline Vector3 * GetRigidbodyPosition()
	{
		auto pRb = this->GetRigidbody();
		if (pRb == nullptr)
			return nullptr;

		return (Vector3*)&pRb->m_pInternalState->m_pInternal2->m_Position;
	}

	inline Vector3 * GetRigidbodyPreviousPosition()
	{
		auto pRb = this->GetRigidbody();
		if (pRb == nullptr)
			return nullptr;

		return (Vector3*)&pRb->m_pInternalState->m_pInternal2->m_PrevPosition;
	}

	inline Vector3 * GetRigidbodyVelocity()
	{
		auto pRb = this->GetRigidbody();
		if (pRb == nullptr)
			return nullptr;

		return (Vector3*)&pRb->m_pInternalState->m_pInternal2->m_Velocity;
	}

	inline bool CanJump()
	{
		auto statePtr = this->m_pAbilities->JumpWrapper->State;

		if (!statePtr)
			return false;

		return ((bool(__fastcall*)(SeinJump*))(Assembly_BaseAddr + GAMEASSEMBLY_SEINJUMP_CANJUMP_RVA))(this->m_pAbilities->JumpWrapper->State);
	}

	inline bool CanDoubleJump()
	{
		auto statePtr = this->m_pAbilities->DoubleJumpWrapper->State;

		if (!statePtr)
			return false;

		if (!statePtr->m_isActive)
			return false;

		return this->IsInAir() && statePtr->m_numberOfJumpsAvailable > 0 && statePtr->m_remainingLockTime <= 0.0f;
	}

	inline bool IsInAir()
	{

		if (0.0001f > this->pPlatformBehaviour->pPlatformMovement->m_LocalSpeed.y)
			return !this->pPlatformBehaviour->pPlatformMovement->m_pOnGround->IsOn;

		return true;
	}

	inline bool CanChargeJump()
	{
		auto statePtr = this->m_pAbilities->ChargeJumpWrapper->State;

		if (!statePtr)
			return false;

		// Check the zones.
		return statePtr->WasGroundedSinceLastExecution && !RestrictAbilityController_IsRestricted(AbilityType::ChargeJumpAbility, SeinAbilityRestrictZoneMask::ChargeJumpZoneMask);

		//return ((bool(__fastcall*)(SeinChargeJump*))(Assembly_BaseAddr + GAMEASSEMBLY_SEINCHARGEJUMP_CANCHARGE_RVA))(this->m_pAbilities->ChargeJumpWrapper->State);
	}

	inline bool CanStartChargingChargeJump()
	{
		auto statePtr = this->m_pAbilities->ChargeJumpWrapper->State;
		
		if (!statePtr)
			return false;

		return ((bool(__fastcall*)(SeinChargeJump*))(Assembly_BaseAddr + GAMEASSEMBLY_SEINCHARGEJUMP_CANSTARTCHARGING_RVA))(this->m_pAbilities->ChargeJumpWrapper->State);

	}
};
#pragma pack(pop)

extern unsigned long long gqw_SeinCharacterPtr;
extern inline SeinCharacter * GetSeinCharacter();


