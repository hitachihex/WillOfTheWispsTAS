#pragma once

#pragma pack(push, 1)

class InheritanceChain
{
public:

	// 0x0000 - 0x0007
	unsigned long long m_Ptr;

	// 0x0008 - 0x000B
	unsigned long m_Index;
protected:
private:
};
class InterfaceDef
{
public:

	// 0x0000 - 0x0007
	unsigned long long m_qwUnk0000_0007;

	// 0x0008 - 0x000F
	unsigned long long m_qwUnk0008_000F;

	// 0x0010 - 0x0017
	char * m_szScriptClassName;

	// 0x0018 - 0x00AF
	unsigned char uc_Unk0000_00AF[0xB0 - 0x18];

	// 0x00B0 - 0x00B7
	InheritanceChain * m_pInheritanceChain;

	// 0x00B8 - 0x011D
	unsigned char uc_Unk00B8_011D[0x11E - 0xB8];

	// 0x011E - 0x011F
	unsigned short m_nInheritedByCount;

	// 0x0120 - 0x0127
	unsigned long long m_qwUnk0120_0127;

	// 0x0128 - 0x012F
	unsigned long long VTable;
protected:
private:
};
#pragma pack(pop)