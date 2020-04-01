#pragma once
#include "Vector3.h"
#pragma pack(push, 1)

typedef struct t_CharacterPlatformMovement
{
	// local speed @ 0x80, let's just get that for now

public:
	
	// 0x00 - 0x7F
	unsigned char uc_Unk0000_007F[0x80];

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
typedef struct t_SeinCharacter
{
public:

	// 0x98 
	// PlatformBehaviour m_PlatformBehaviour

	// 0x00 - 0x97
	unsigned char uc_Unk0000_0097[0x98];

	// 0x98 - ??
	PlatformBehaviour * pPlatformBehaviour;

	
	/*
	inline Vector3 * GetLocalSpeed()
	{
		unsigned long long PlatformBehaviour = *(unsigned long long*)((unsigned long)this + 0x98);
		unsigned long long PlatformMovement = *(unsigned long long*)(PlatformBehaviour + 0x18);

		return (Vector3*)(*(unsigned long long*)(PlatformMovement + 0x80));
	}*/
} SeinCharacter;
#pragma pack(pop)

extern unsigned long long gqw_SeinCharacterPtr;
extern inline SeinCharacter * GetSeinCharacter();


