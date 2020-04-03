#include "stdafx.h"
#include "SeinDashNew.h"
#include "SeinCharacter.h"

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

fnSeinDashNew_CanDash SeinDashNew_CanDash = (fnSeinDashNew_CanDash)(0x0);