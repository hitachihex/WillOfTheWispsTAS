#include "stdafx.h"
#include "Core_Input.h"

unsigned long long gqw_CoreInputInstancePtr = 0x0;

inline Core_Input * GetCoreInputInstance()
{
	unsigned long long rax = *(unsigned long long*)(gqw_CoreInputInstancePtr);
	rax = *(unsigned long long*)(rax + 0xB8);

	return (Core_Input*)(rax);
}