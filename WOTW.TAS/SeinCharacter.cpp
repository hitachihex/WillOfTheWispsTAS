#include "stdafx.h"
#include "EasyHookUtils.h"
#include "SeinCharacter.h"


static constexpr float epsilon = 0.0001f;
static constexpr float re = 0.0f;
unsigned long long gqw_SeinCharacterPtr = 0x0;

inline SeinCharacter * GetSeinCharacter()
{
	unsigned long long rax = *(unsigned long long*)(gqw_SeinCharacterPtr);

	rax = *(unsigned long long*)(rax + 0xB8);

	rax = *(unsigned long long*)(rax + 0x10);

	return (SeinCharacter*)(rax);
}

bool SeinCharacter::IsOnWall()
{
	float LocalSpeedX = this->pPlatformBehaviour->pPlatformMovement->m_LocalSpeed.x;

	if (LocalSpeedX < 0.0f)
		return this->pPlatformBehaviour->pPlatformMovement->m_pWallLeft->IsOn;

	return this->pPlatformBehaviour->pPlatformMovement->m_pWallRight->IsOn;

}

bool SeinCharacter::IsFalling()
{
	CharacterPlatformMovement * pPlatformMovement = this->pPlatformBehaviour->pPlatformMovement;

	bool ret = false;
	if (pPlatformMovement->m_LocalSpeed.y > epsilon)
	{
		// says we're on ground, guess we aren't falling.
		if (pPlatformMovement->m_pOnGround->IsOn)
			ret = false;
	}
	else
	{
		if (pPlatformMovement->m_LocalSpeed.y <= re)
			ret = true;
	}

	return ret;
}

Rigidbody * SeinCharacter::GetRigidbody()
{
	return this->pPlatformBehaviour->pPlatformMovement->m_pRigidbody;
}

void SeinCharacter::SetRigidbodyPosition(float newX, float newY, float newZ, bool setPrevious=true)
{
	auto pRb = this->GetRigidbody();
	pRb->m_pInternalState->m_pInternal2->m_Position.Set(newX, newY, newZ);
	if (setPrevious)
		pRb->m_pInternalState->m_pInternal2->m_PrevPosition.Set(newX, newY, newZ);
}

void SeinCharacter::SetVelocity(float newX, float newY, float newZ, bool setPrevious = true)
{
	auto pRb = this->GetRigidbody();
	pRb->m_pInternalState->m_pInternal2->m_Velocity.Set(newX, newY, newZ);

	// if(setPrevious)
}


Vector3 * SeinCharacter::GetRigidbodyPosition()
{
	return (Vector3*)&this->GetRigidbody()->m_pInternalState->m_pInternal2->m_Position;
}

Vector3 * SeinCharacter::GetRigidbodyPreviousPosition()
{
	return (Vector3*)&this->GetRigidbody()->m_pInternalState->m_pInternal2->m_PrevPosition;
}

Vector3 * SeinCharacter::GetRigidbodyVelocity()
{
	return (Vector3*)&this->GetRigidbody()->m_pInternalState->m_pInternal2->m_Velocity;
}
