#include "stdafx.h"
#include "SeinWallJump.h"
#include "SeinCharacter.h"

fnSeinWallJump_CanPerformWallJump SeinWallJump_CanPerformWallJump = (fnSeinWallJump_CanPerformWallJump)(0x0);

/*
bool SeinWallJump::CanPerformWallJump()
{
	if (!this->m_isActive)
		return false;

	// check for UnityEngine.Behaviour::get_enabled()
	if (this->m_pInternalBehaviour->IsEnabled())
		return false;

	auto pPlatformMovement = this->m_pSein->pPlatformBehaviour->pPlatformMovement;
	return true;
}*/