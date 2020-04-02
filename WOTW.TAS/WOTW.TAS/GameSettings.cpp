#include "stdafx.h"
#include "GameSettings.h"

unsigned long long gqw_GameSettingsInstance_Ptr = 0x0;

inline GameSettings * GetGameSettingsInstance()
{
	unsigned long long rax = *(unsigned long long*)(gqw_GameSettingsInstance_Ptr);
	unsigned long long rcx = *(unsigned long long*)(rax + 0xB8);
	rax = *(unsigned long long*)(rcx);

	return (GameSettings*)(rax);
}