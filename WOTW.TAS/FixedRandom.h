#pragma once

#include "Vector2.h"
#include "Vector3.h"

//.data:00000001843FDB58 gameassembly.dll:$43FDB58 #0
#define FIXEDRANDOM_INSTANCEPTR_RVA 0x43FDB58
#pragma pack(push, 1)

class FixedRandom
{
public:

	// 0x00 - 0x03
	int FixedUpdateIndex;

	// 0x04 - 0x07
	int AmountOfValues;

	// 0x08 - 0x0F
	float * Values;

	// 0x10 - 0x17
	Vector2 * InsideUnitCircleValues;

	// 0x18 - 0x23
	Vector3 * InsideUnitSphereValues;

protected:
private:
};
#pragma pack(pop)

extern unsigned long long gqw_FixedRandomInstancePtr;
extern inline FixedRandom * GetFixedRandomInstance();
