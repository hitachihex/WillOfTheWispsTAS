#pragma once

#include <wchar.h>

#pragma pack(push, 1)

class String
{
public:

	String()
	{

		// it doesn't really care what these are, it does not use them
		this->m_qwUnk0000_0007 = 0x0;
		this->m_qwUnk0008_000F = 0x0;

		this->m_nLength = 0;
		wmemset(&this->m_wszBytes[0], 0x0, 512 * 4);
	}
	// 0x0000 - 0x0007
	unsigned long long m_qwUnk0000_0007;

	// 0x0008 - 0x000F
	unsigned long long m_qwUnk0008_000F;

	// 0x0010 - 0x0013
	unsigned long m_nLength;


	// This expands
	// 0x0014 - 
	wchar_t m_wszBytes[512 * 4];

	static void Set(String* ref, const wchar_t* newBytes)
	{
		ref->m_nLength = ua_wcslen(newBytes) + 1;
		wmemset(&ref->m_wszBytes[0], 0x0, 512 * 4);
		wmemcpy(&ref->m_wszBytes[0], newBytes, ref->m_nLength);
	}

	static void Recalcuate(String *ref)
	{
		ref->m_nLength = ua_wcslen(ref->m_wszBytes) + 1;
	}
	static void Clear(String *ref)
	{
		ref->m_nLength = 0;
		wmemset(&ref->m_wszBytes[0], 0x0, 512 * 4);
	}
protected:
private:
};
#pragma pack(pop)