#include "stdafx.h"
#include "EasyHookUtils.h"
#include "SeinCharacter.h"


static constexpr float epsilon = 0.0001f;
static constexpr float re = 0.0f;
unsigned long long gqw_SeinCharacterPtr = 0x0;

inline SeinCharacter * GetSeinCharacter()
{
	unsigned long long rax = *(unsigned long long*)(gqw_SeinCharacterPtr);

	if (!rax)
		return nullptr;

	rax = *(unsigned long long*)(rax + 0xB8);

	if (!rax)
		return nullptr;

	rax = *(unsigned long long*)(rax + 0x10);

	return (SeinCharacter*)(rax);
}

std::string SeinCharacter::GetConditionalCharacterStateInfo()
{
	std::string output = "";

	if (this->CanJump())
		output += "CanJump, ";

	ISWRAPPERSTATEVALID(this, DashNewWrapper)
	{
		if (SeinDashNew_CanDash(this->m_pAbilities->DashNewWrapper->State))
			output += "CanDash, ";
	}

	ISWRAPPERSTATEVALID(this, WallJumpWrapper)
	{
		if (EXW4M(this, WallJumpWrapper)->CanPerformWallJump())
			output += "CanWallJump, ";
	}

	if (this->CanDoubleJump())
		output += "CanDJump, ";
	
	if (this->CanChargeJump())
		output += "CanLaunch, ";

	return output;
}

#pragma warning(disable : 4996)
std::string SeinCharacter::GetActiveCharacterStateInfo()
{

	bool isDashing = false;

	std::string output = "";

	if (this->pPlatformBehaviour->pPlatformMovement->m_pOnGround->IsOn)
		output += "Grounded, ";

	if (this->pPlatformBehaviour->pPlatformMovement->m_pCeiling->IsOn)
		output += "OnCeiling, ";

	if (this->IsOnWall())
		output += "OnWall, ";

	if (this->IsInAir())
		output += "InAir, ";

	if (this->IsFalling())
		output += "Falling, ";

	ISWRAPPERSTATEVALID(this, DashNewWrapper)
	{
		if (EXW4M(this, DashNewWrapper)->m_isDashing)
		{
			output += "Dashing, ";
			isDashing = true;
		}
	}

	ISWRAPPERSTATEVALID(this, ComboWrapper)
	{
		if (EXW4M(this, ComboWrapper)->m_pCurrentComboMove != nullptr)
		{
			auto pccm = EXW4M(this, ComboWrapper)->m_pCurrentComboMove;
			
			output += "AbilityType: ";
			auto abType = (unsigned int)pccm->get_ComboAbilityType();
			output += std::to_string(abType);
			output += ", ";


			/*
			ComboMoveType cmt = EXW4M(this, ComboWrapper)->m_pCurrentComboMove->get_ComboMoveType();
			char * pszScriptClassName = EXW4M(this, ComboWrapper)->m_pCurrentComboMove->m_pInterfaceDef->m_szScriptClassName;
			switch (cmt)
			{
			case ComboMoveType::Attack:
				output += "IsAttack <";
				output += pszScriptClassName;
				output += ">, ";
				break;
			case ComboMoveType::MovementAbility:
				output += "IsAbility <";
				output += pszScriptClassName;
				output += ">, ";
				break;
			case ComboMoveType::ComboMove_Any:
				output += "IsAny <";
				output += pszScriptClassName;
				output += ">, ";
				break;
			default:
				break;

			}*/
				
		}
	}
	else
		output += "ComboWrapper state invalid.";


	return output;
}



