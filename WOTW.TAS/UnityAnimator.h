#pragma once

#include "UnityPlayer.h"
#pragma pack(push, 1)

class UnityAnimator_Internal
{
public:
	// 0x00 - 0x07
	unsigned long long m_qwUnk0000_0007;

	// 0x08 - 0x0F
	unsigned long long m_qwUnk0008_000F;

	// 0x10 - 0x370
	unsigned char uc_Unk0010_0036F[0x371 - 0x10];

	// 0x371
	bool m_bApplyRootMotion;
protected:
private:
};
class UnityAnimator
{
public:

	// 0x00 - 0x07
	unsigned long long m_qwUnk0000_0007;

	// 0x08 - 0x0F
	unsigned long long m_qwUnk0008_000F;

	// 0x10 - 0x17
	UnityAnimator_Internal * m_pInternal;
protected:
private:
};
#pragma pack(pop)

typedef unsigned int(__fastcall * fnUnityEngine_Animator_GetUpdateMode)(UnityAnimator*);
extern fnUnityEngine_Animator_GetUpdateMode UnityEngine_Animator_GetUpdateMode;

