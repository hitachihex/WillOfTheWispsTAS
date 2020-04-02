#pragma once

#include "Addresses.h"
#include "UnityEngine_PhysicsSettings.h"
#include "UnityEngine_Input.h"
#include "UI_Cameras.h"
#include "UnityPlayer.h"
#include "Core_Input.h"

static UnityEngine_Input * GetUnityEngine_Input()
{
	unsigned long long rax = *(unsigned long long*)(((UnityPlayer_BaseAddr)+UNITYENGINE_INDEXER_PTR_RVA) + UNITYENGINE_INPUT_INDEX * 0x08);
	return (UnityEngine_Input*)(rax);
}

static inline UnityEngine_PhysicsSettings * GetPhysicsSettings()
{
	unsigned long long rax = *(unsigned long long*)(((UnityPlayer_BaseAddr)+UNITYENGINE_INDEXER_PTR_RVA) + UNITYENGINE_PHYSICS_INDEX * 0x08);
	return (UnityEngine_PhysicsSettings*)(rax);
}

static inline void SetFixedDeltaTime(float newFixedDelta)
{
	GetPhysicsSettings()->m_fFixedDeltaTime = newFixedDelta;
}

static inline unsigned long long RelativeAddressCalcFromDatasegment(unsigned long long virtualAddress, unsigned int offset)
{
	unsigned long long VAToInstruction = (virtualAddress + offset);
	unsigned long long relativeCalc = *(unsigned long*)(VAToInstruction + 0x03);
	unsigned long long resultVA = (VAToInstruction + relativeCalc) + 0x07;

	return resultVA;
}