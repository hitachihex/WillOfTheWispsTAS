#pragma once

#include "Vector3.h"
#include "Rigidbody.h"
#include "IsOnCollisionState.h"
#pragma pack(push,1)

class CharacterPlatformMovement
{
	// local speed @ 0x80, let's just get that for now

public:

	// 0x00 - 0x1F
	unsigned char uc_Unk0000_007F[0x20];

	// 0x20 - 0x27
	IsOnCollisionState * m_pCeiling;

	// 0x28 - 0x2F
	IsOnCollisionState * m_pOnGround;

	// 0x30 - 0x37
	IsOnCollisionState * m_pWallLeft;

	// 0x38 - 0x3F
	IsOnCollisionState * m_pWallRight;

	// 0x40 - 0x4B
	Vector3 CeilingNormal;

	// 0x4C - 0x57
	Vector3 GroundNormal;

	// 0x58 - 0x63
	Vector3 WallRightNormal;

	// 0x64 - 0x6F
	Vector3 WallLeftNormal;

	// 0x70 - 0x73
	float fallTime;

	// 0x74 - 0x77
	float landTime;

	// 0x78 - 0x7B
	float ClimbableWallAngleLimit;

	// 0x7C - 0x7F
	float LastTimeOnGround;

	// 0x80 -  0x8B
	Vector3 m_LocalSpeed;

	// 0x8C - 0xCF
	unsigned char uc_Unk008C_00CF[0xD0 - 0x8C];

	// 0xD0 - 0xDB
	Vector3 m_PreviousPosition;

	// 0xDC
	bool m_b00DC;

	// 0xDD
	bool m_b00DD;

	// 0xDE
	bool m_b00DE;

	// 0xDF
	bool m_b00DF;

	// 0xE0 - 0xE7
	Rigidbody * m_pRigidbody;

	// 0xE8 - ??

	// methods
	/*
	inline bool IsOnClimbableWall()
	{

	}*/

};
#pragma pack(pop)