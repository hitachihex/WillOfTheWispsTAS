#pragma once

#pragma pack(push, 1)
typedef struct t_CompoundButtonInput
{

	// 0x00 - 0x07
	unsigned long long m_dwInstanceInfo;

	// 0x08 - 0x0B
	unsigned long m_dwUnk08_0B;

	// 0x0C - 0x0F
	unsigned long m_dwUnk0C_0F;

	// 0x10 - 0x17
	unsigned long long m_dwObjAddr;
} CompoundButtonInput;

#pragma pack(pop)