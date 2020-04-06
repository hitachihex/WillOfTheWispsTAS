#include "stdafx.h"
#include "EverythingNeedsMe.h"
#include "EasyHookUtils.h"
#include "SeinDashNew.h"
#include "SeinCharacter.h"

HOOK_TRACE_INFO SeinDashNew_OnProcessRootMotion_HookHandle = { NULL };
void SeinDashNew::UpdateDash()
{
	float predictedTravelDistance = this->m_predictedTravelDistance;
	if (predictedTravelDistance > 0)
	{
		float deltaDistanceTravelled = (predictedTravelDistance - this->m_currentDistanceTravelled);

		this->m_rootMotionScale = this->GetRootMotionScale(deltaDistanceTravelled);

		SeinCharacter * pSein = this->m_pSein;
		
		if (!pSein)
			return;

		int edx = (this->m_facingDirection >> 0x1F);

		// call gameassembly.57A7910

		float seinCharLocalYSpeed = pSein->pPlatformBehaviour->pPlatformMovement->m_LocalSpeed.y;

		if (seinCharLocalYSpeed > 0.0001f && pSein->pPlatformBehaviour->pPlatformMovement->m_pOnGround->IsOn)
		{
			
		}
		else
		{
			// Not on ground
		}
	}
	else
	{

	}
}

float SeinDashNew::GetRootMotionScale(float rootMotionDistance)
{
	return 0.0f;
}

void __fastcall SeinDashNew_OnProcessRootMotion_Hook(SeinDashNew* pThis, Vector3 * rootVelocity)
{
	DoOnceBlock("SeinDashNew_OnProcessRootMotion_Hook, !bOnce");

	/* And nope, only works when something does not implement OnAnimatorMove (Moon does.)
	if (pThis->m_isDashing)
	{
		pThis->m_pSeinAnimator->m_pUnityAnimator->m_pInternal->m_bApplyRootMotion = false;
	}*/
	/* No.
	if (pThis->m_isDashing)
	{
		if (!Rigidbody_GetIsKinematic(pThis->m_pSein->pPlatformBehaviour->pPlatformMovement->m_pRigidbody))
			Rigidbody_SetIsKinematic(pThis->m_pSein->pPlatformBehaviour->pPlatformMovement->m_pRigidbody, true);
	}*/

	return original_SeinDashNew_OnProcessRootMotion(pThis, rootVelocity);
}

// do this in NativeInjectionEntryPoint
fnSeinDashNew_OnProcessRootMotion original_SeinDashNew_OnProcessRootMotion = (fnSeinDashNew_OnProcessRootMotion)(0x0);
fnSeinDashNew_CanDash SeinDashNew_CanDash = (fnSeinDashNew_CanDash)(0x0);