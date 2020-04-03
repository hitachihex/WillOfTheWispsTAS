#pragma once
#pragma pack(push,1)

class SeinCharacter;

class CharacterState
{
public:
	// 0x0000 - 0x0057
	unsigned char uc_Unk0000_0057[0x58];

	// 0x58 - 0x5F
	SeinCharacter * m_pSein;

	// 0x60
	bool m_isActive;

	// 0x61
	bool m_b0061;

	// 0x62
	bool m_b0062;

	// 0x63
	bool m_b0063;

	// 0x64
	bool m_b0064;

	// 0x65
	bool m_b0065;

	// 0x66
	bool m_b0066;

	// 0x67
	bool m_b067;

	// 0x68 - 0x6F
	unsigned long long bool_Array_m_canBeInterruptedBy;

	// 0x70
	bool m_canInputBeQueued;

	// 0x71
	bool m_b0071;

	// 0x72
	bool m_b0072;

	// 0x73
	bool m_b0073;

	// 0x74
	bool m_b0074;

	// 0x75
	bool m_b0075;

	// 0x76
	bool m_b0076;

	// 0x77
	bool m_b0077;

	// 0x78 - 0x7F
	unsigned long long string_CharacterStateUpdateString;

protected:
private:

};
#pragma pack(pop)
