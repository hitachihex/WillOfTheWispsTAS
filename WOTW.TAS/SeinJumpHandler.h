#pragma once

#include "CharacterState.h"
#pragma pack(push, 1)

class SeinJumpHandler
{
public:

	// 0x0000 - 0x0007
	unsigned long long m_qwUnk0000_0007;

	// 0x0008 - 0x000F
	unsigned long long m_qwUnk0000_000F;
	
	// 0x0010
	bool m_isBlindForest;

	// 0x0011
	bool m_b0011;

	// 0x0012
	bool m_b0012;

	// 0x0013
	bool mb_0013;

	// 0x0014
	bool m_b0014;

	// 0x0015
	bool m_b0015;

	// 0x0016
	bool m_b0016;

	// 0x0017
	bool m_b0017;

	// 0x0018 - 0x001F
	CharacterState * m_pLastJumpExecuted;
protected:
private:
};
#pragma pack(pop)
