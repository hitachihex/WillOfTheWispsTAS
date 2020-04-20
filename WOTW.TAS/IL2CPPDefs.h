#pragma once
#pragma pack(push, 1)

typedef struct t_IL2CppMethod
{
	// 0x0000 - 0x0007
	unsigned long long * pImage;

	// 0x0008 - 0x000F
	unsigned long long * pGarbageCollectionDescriptor;

	// 0x0010 - 0x0017
	const char * pcszMethodName;
} IL2CppMethod;

typedef struct IL2CppClass
{
	// 0x0000 - 0x0007
	unsigned long long * pImage;

	// 0x0008 - 0x000F
	unsigned long long * pGarbageCollectionDescriptor;

	// 0x0010 - 0x0017
	const char * pcszClassName;
} IL2CppClass;

typedef struct MethodInfo
{
	// 0x0000 - 0x0007
	unsigned long long methodAddr;

	// 0x0008 - 0x000F
	unsigned long long invokerAddr;

	// 0x0010 - 0x0017
	const char* pcszMethodName;

	// 0x0018 - 0x001F
	IL2CppClass *pClass;

} MethodInfo;
#pragma pack(pop)
