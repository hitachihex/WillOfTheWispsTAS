#pragma once
#include "CharacterState.h"
#include "UnityEngineBehavour.h"

#define SEINWALLJUMP_CANPERFORMWALLJUMP_RVA 0xC29C00


// forward me please
class SeinWallJump;
typedef bool(__fastcall * fnSeinWallJump_CanPerformWallJump)(SeinWallJump*);
extern fnSeinWallJump_CanPerformWallJump SeinWallJump_CanPerformWallJump;

#pragma pack(push, 1)

class SeinWallJump : public CharacterState
{
public:
	// 0x00 - 0x7F = CharacterState members

	// 0x80 - 0xC7
	unsigned char uc_Unk0080_00C7[0xC8];

	// methods
	inline bool CanPerformWallJump()
	{
		return SeinWallJump_CanPerformWallJump(this);
	}
protected:
private:
};


#pragma pack(pop)


