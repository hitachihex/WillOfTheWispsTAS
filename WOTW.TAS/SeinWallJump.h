#pragma once
#include "CharacterState.h"
#define SEINWALLJUMP_CANPERFORMWALLJUMP_RVA 0xC27230

#pragma pack(push, 1)

class SeinWallJump : CharacterState
{
public:
protected:
private:
};


#pragma pack(pop)


typedef bool(__fastcall * fnSeinWallJump_CanPerformWallJump)(SeinWallJump*);
extern fnSeinWallJump_CanPerformWallJump SeinWallJump_CanPerformWallJump;
