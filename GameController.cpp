#include "stdafx.h"
#include "GameController.h"

unsigned long long gqw_GameControllerInstancePtr = 0x0;
GameController * g_pGameControllerInstance = nullptr;

inline GameController * GetGameControllerInstance()
{
	// deref 0
	unsigned long long rax = *(unsigned long long*)(gqw_GameControllerInstancePtr);

	// deref 0xB8
	rax = *(unsigned long long*)(rax + 0xB8);

	return (GameController*)(rax);
}