#include "stdafx.h"
#include "FixedRandom.h"

unsigned long long gqw_FixedRandomInstancePtr = 0x0;

inline FixedRandom * GetFixedRandomInstance()
{
	
	unsigned long long rax = *(unsigned long long*)(gqw_FixedRandomInstancePtr);

	rax = *(unsigned long long*)(rax + 0xB8);

	return (FixedRandom*)(rax);
}