#include "stdafx.h"
#include "EasyHookUtils.h"
#include "SeinCharacter.h"

unsigned long long gqw_SeinCharacterPtr = 0x0;


// prod it, slightly
inline SeinCharacter * GetSeinCharacter()
{
	// deref 0

	unsigned long long rax = *(unsigned long long*)(gqw_SeinCharacterPtr);
	//DebugOutput("Dereferenced 0x0 (SeinCharPtr)");

	rax = *(unsigned long long*)(rax + 0xB8);
	//DebugOutput("Dereferenced 0xB8 (SeinCharPtr)");

	rax = *(unsigned long long*)(rax + 0x10);
	//DebugOutput("Dereferenced 0x10 (SeinCharPtr)");

	return (SeinCharacter*)(rax);
}

bool SeinCharacter::IsOnWall()
{
	float LocalSpeedX = this->pPlatformBehaviour->pPlatformMovement->m_LocalSpeed.x;

	if (LocalSpeedX < 0.0f)
		return this->pPlatformBehaviour->pPlatformMovement->m_pWallLeft->IsOn;

	return this->pPlatformBehaviour->pPlatformMovement->m_pWallRight->IsOn;

}

bool SeinCharacter::IsFaling()
{
	CharacterPlatformMovement * pPlatformMovement = this->pPlatformBehaviour->pPlatformMovement;

	bool ret = false;
	if (pPlatformMovement->m_LocalSpeed.y > 0.0001f)
	{
		// says we're on ground, guess we aren't falling.
		if (pPlatformMovement->m_pOnGround->IsOn)
			ret = false;
	}
	else
	{
		if (pPlatformMovement->m_LocalSpeed.y <= 0.0f)
			ret = true;
	}

	return ret;
}
