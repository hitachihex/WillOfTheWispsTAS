#pragma once
#pragma pack(push, 1)
typedef struct IL2CppClass
{
	// 0x00 - 0x07
	unsigned long long * pImage;

	// 0x08 - 0xE
	unsigned long long * pGarbageCollectionDescriptor;

	// 0x0F - 0x15
	const char * pcszClassName;
} IL2CppClass;

typedef struct MethodInfo
{
	// 0x00 - 0x07
	unsigned long long methodAddr;

	// 0x08 - 0xE
	unsigned long long invokerAddr;

	// 0x0F - 0x15
	const char* pcszMethodName;

	// 0x16 - 0x1D
	IL2CppClass *pClass;

} MethodInfo;
#pragma pack(pop)
