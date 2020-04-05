#include "stdafx.h"
#include "EasyHookUtils.h"
#include "SeinCharacter.h"


static constexpr float epsilon = 0.0001f;
static constexpr float re = 0.0f;
unsigned long long gqw_SeinCharacterPtr = 0x0;

inline SeinCharacter * GetSeinCharacter()
{
	unsigned long long rax = *(unsigned long long*)(gqw_SeinCharacterPtr);

	rax = *(unsigned long long*)(rax + 0xB8);

	rax = *(unsigned long long*)(rax + 0x10);

	return (SeinCharacter*)(rax);
}


