#include "stdafx.h"
#include "UnityEngineEvent.h"

unsigned long long g_qwUnityEventCurrent_InstancePtr = 0x0;

UnityEvent * GetCurrentEventInstance()
{
	unsigned long long rax = *(unsigned long long*)((Assembly_BaseAddr) + GAMEASSEMBLY_UNITYEVENT_CURRENT_RVA);

	if(!rax)
		return nullptr;

	rax = *(unsigned long long*)(rax + 0xB8);

	rax = *(unsigned long long*)(rax);

	return (UnityEvent*)(rax);
}