#pragma once

#include "Vector3.h"

#define UNITYPLAYER_RIGIDBODY_SETISKINEMATIC_RVA 0x40D000

#pragma pack(push, 1)

class Rigidbody_Internal2
{
public:
	// 0x0000 - 0x009F
	unsigned char uc_Unk0000_009F[0xA0];

	// 0xA0 - 0xAB
	Vector3 m_PrevPosition;

	// 0xAC - 0x14F
	unsigned char uc_Unk00AC_014F[0x150 - 0xAC];

	// 0x150 - 0x15B
	Vector3 m_Position;

	// 0x15C - 0x167
	Vector3 m_Velocity;
protected:
private:
};
class Rigidbody_Internal
{
public:
	// 0x0000 - 0x005F
	unsigned char uc_Unk0000_0097[0x60];

	// 0x60 - 0x67
	Rigidbody_Internal2 * m_pInternal2;

	// 0x68 - 0x97
	unsigned char uc_Unk0068_0097[0x98 - 0x68];

	// 0x98
	bool m_bIsKinematic;
protected:
private:
};
class Rigidbody
{
public:

	// 0x00 - 0x07
	unsigned long long m_qwUnk00_07;

	// 0x08 - 0x0F
	unsigned long long m_qwUnk08_0F;

	// 0x10 - 0x17
	Rigidbody_Internal * m_pInternalState;
protected:
private:
};
#pragma pack(pop)

typedef bool(__fastcall * fnRigidbody_GetIsKinematic)(Rigidbody*);
extern fnRigidbody_GetIsKinematic Rigidbody_GetIsKinematic;

typedef void(__fastcall * fnRigidbody_SetIsKinematic)(Rigidbody*, bool);
extern fnRigidbody_SetIsKinematic Rigidbody_SetIsKinematic;