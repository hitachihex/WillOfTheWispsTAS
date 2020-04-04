#pragma once

#include "MoonAnimator.h"
#pragma pack(push, 1)

class CharacterVisuals
{
public:

	// 0x00 - 0x07
	unsigned long long m_dwUnk0000_0007;

	// 0x08 - 0x0F
	unsigned long long m_dwUnk0008_000F;

	// 0x10 - 0x17
	unsigned long long CharacterSpriteMirror_SpriteMirror;

	// 0x18 - 0x1F
	unsigned long long CharacterAnimationSystem_Animation;

	// 0x20 - 0x27
	MoonAnimator * m_pAnimator;
protected:
private:
};
#pragma pack(pop)