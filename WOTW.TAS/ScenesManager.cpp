#include "stdafx.h"
#include "ScenesManager.h"

unsigned long long gqw_ScenesManagerInstancePtr = 0x0;
ScenesManager * g_pScenesManager = nullptr;

fnScenesManager_IsPositionInsideSceneStillLoading ScenesManager_IsPositionInsideSceneStillLoading = (fnScenesManager_IsPositionInsideSceneStillLoading)(0x0);

inline ScenesManager * GetScenesManagerInstance()
{
	unsigned long long rax = *(unsigned long long*)(gqw_ScenesManagerInstancePtr);

	rax = *(unsigned long long*)(rax + 0xB8);

	rax = *(unsigned long long*)(rax);

	return (ScenesManager*)(rax);
}