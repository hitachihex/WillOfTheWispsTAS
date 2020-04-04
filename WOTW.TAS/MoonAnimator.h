#pragma once
#include "UnityAnimator.h"
#pragma pack(push, 1)

class MoonAnimator
{
public:

	// 0x0000 - 0x011F
	unsigned char uc_Unk0000_011F[0x120];

	// 0x120 - 0x127
	UnityAnimator * m_pUnityAnimator;

	// 0x128 - 0x12F
	// Maybe this isn't even a pointer, this struct might be very tiny.
	unsigned long long PlayableGraph_Temp;
protected:
private:

};
#pragma pack(pop)
