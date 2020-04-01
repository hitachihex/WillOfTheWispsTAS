#pragma once

#include "SeinCharacter.h"
#pragma pack(push, 1)

typedef struct t_Characters
{
	// 0x00
	bool HasSein;

	// 0x01
	bool HasBabySein;

	// 0x02
	bool HasNaru;

	// 0x03
	bool HasKu;

	// 0x04 - 0x07
	unsigned long m_dwUnk04_07;

	
	// 0x08 - 0x0B
	unsigned long m_dwUnk08_0B;

	// 0x0C - 0x0F
	unsigned long m_dwUnk0C_0F;

	// 0x10
	SeinCharacter * m_pSein;


	// BabySein..

	// Naru..

	// Ku..


} Characters;


#pragma pack(pop)
