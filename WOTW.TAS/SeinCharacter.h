#pragma once
#include "Vector3.h"
//#include "CharacterState.h"
#include "CharacterPlatformMovement.h"
#include "PlatformBehaviour.h"
#include "SeinAbilities.h"
#include "SeinLogicCycle.h"
#include "EverythingNeedsMe.h"
#pragma pack(push, 1)


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


