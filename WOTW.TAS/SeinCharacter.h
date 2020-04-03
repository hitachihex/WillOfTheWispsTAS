#pragma once
#include "Vector3.h"
//#include "CharacterState.h"
#include "SeinAbilities.h"
#include "IsOnCollisionState.h"
#pragma pack(push, 1)


typedef struct t_CharacterPlatformMovement
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

} CharacterPlatformMovement;

typedef struct t_PlatformBehaviour
{
public:
	// 0x00 - 0x17
	unsigned char uc_Unk0000_0017[0x18];

	// 0x18 - ??
	CharacterPlatformMovement * pPlatformMovement;
} PlatformBehaviour;

class SeinCharacter
{
public:

	// 0x98 
	// PlatformBehaviour m_PlatformBehaviour

	// 0x00 - 0x17
	unsigned char uc_Unk0000_0017[0x18];

	// 0x18 - 0x1F
	unsigned long long SeinLogicCycle_LogicCycle;

	// 0x20 - 0x27
	SeinAbilities * m_pAbilities;

	// 0x28 - 0x97
	unsigned char uc_Unk0028_0097[0x98 - 0x28];

	// 0x98 - 0x9F
	PlatformBehaviour * pPlatformBehaviour;

	
	/*
	inline Vector3 * GetLocalSpeed()
	{
		unsigned long long PlatformBehaviour = *(unsigned long long*)((unsigned long)this + 0x98);
		unsigned long long PlatformMovement = *(unsigned long long*)(PlatformBehaviour + 0x18);

		return (Vector3*)(*(unsigned long long*)(PlatformMovement + 0x80));
	}*/

	// ----- methods
	bool IsOnWall();

	bool IsFaling();

};
#pragma pack(pop)

extern unsigned long long gqw_SeinCharacterPtr;
extern inline SeinCharacter * GetSeinCharacter();


