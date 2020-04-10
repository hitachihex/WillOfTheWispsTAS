#include "stdafx.h"
#include "Screen.h"

unsigned long long g_qwScreenInstancePtr = 0x0;

Screen * GetScreenInstance()
{
	unsigned long long rax = *(unsigned long long*)(g_qwScreenInstancePtr);

	return (Screen*)(rax);
}