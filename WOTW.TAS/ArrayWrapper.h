#pragma once

#pragma pack(push, 1)

template<typename T>
class ArrayWrapper
{
public:

	// 0x0000 - 0x0017
	unsigned char uc_Unk0000_0017[0x18];

	// 0x18 - 0x1B
	unsigned long m_nElements;

	// 0x1C - 0x1F
	unsigned long m_dwUnk001C_001F;

	// Elements start here
	// 0x20 - ??
	T * m_Elements;

protected:
private:
};


template  <typename T, unsigned int S>
class FixedArrayWrapper
{
public:
	// 0x0000 - 0x0017
	unsigned char uc_Unk0000_0017[0x18];

	// 0x18 - 0x1B
	unsigned long m_nElements;

	// 0x1C - 0x1F
	unsigned long m_dwUnk001C_001F;

	T m_Elements[S];

protected:
private:
};
#pragma pack(pop)