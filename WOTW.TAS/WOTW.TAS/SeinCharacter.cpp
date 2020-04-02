#include "stdafx.h"
#include "EasyHookUtils.h"
#include "SeinCharacter.h"

unsigned long long gqw_SeinCharacterPtr = 0x0;


// prod it, slightly
inline SeinCharacter * GetSeinCharacter()
{
	// deref 0

	unsigned long long rax = *(unsigned long long*)(gqw_SeinCharacterPtr);
	//DebugOutput("Dereferenced 0x0 (SeinCharPtr)");

	rax = *(unsigned long long*)(rax + 0xB8);
	//DebugOutput("Dereferenced 0xB8 (SeinCharPtr)");

	rax = *(unsigned long long*)(rax + 0x10);
	//DebugOutput("Dereferenced 0x10 (SeinCharPtr)");

	return (SeinCharacter*)(rax);
}