#include "stdafx.h"
#include "Cmd.h"

unsigned long long gqw_CmdInstancePtr = 0x0;

inline Cmd * GetCmdInstance()
{
	unsigned long long rax = *(unsigned long long*)(gqw_CmdInstancePtr);
	rax = *(unsigned long long*)(rax + 0xB8);

	return (Cmd*)(rax);
}