#pragma once
#include "IL2CPPDefs.h"
#pragma pack(push, 1)

typedef struct t_MethodTable
{
public:

	// 0x0000 - 0x0007
	unsigned long long MethodAddress;

	// 0x0008 - 0x000F
	IL2CppMethod * pMethodArgument;

	// --- m
	template<typename T>
	T As(void* pInstance)
	{
		return ((T(__fastcall*)(void*, IL2CppMethod*))this->MethodAddress)(pInstance, this->pMethodArgument);
	}
protected:
private:
} MethodTable;

#pragma pack(pop)