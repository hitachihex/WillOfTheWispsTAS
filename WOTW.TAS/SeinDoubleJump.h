#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include <easyhook.h>
#include "EverythingNeedsMe.h"
#include "CharacterState.h"

#pragma pack(push, 1)

class SeinDoubleJump : public CharacterState
{
public:
	// 0x00 - 0x7F = CharacterState members

	// 0x80 - 0x83
	float JumpStrength;

	// 0x84 - 0x87
	unsigned long dw_Unk0084_0087;

	// 0x88 - 0x8F
	unsigned long long SoundPlayer_m_doubleJumpSound;

	// 0x90 - 0x93
	float m_doubleJumpTime;

	// 0x94 - 0x97
	int m_numberOfJumpsAvailable;

	// 0x98 - 0x9B
	float m_remainingLockTime;

	// 0x9C 
	bool m_isDoubleJumping;

	// 0x9D
	bool m_isInAirCached;

	// 0x9E
	bool m_b009E;

	// 0x9F
	bool m_b009F;

	// 0xA0 - 0xA7
	unsigned long long WwiseEventSystem_SoundHandle_m_doubleJumpSoundHandler;

	// 0xA8 - 0xAF
	unsigned long long m_qwUnk00A8_00AF;

	// 0xB0 - 0xB7
	unsigned long long m_qwUnk00B0_00B7;

	// 0xB8 - 0xBF
	float m_earliestCancelTime;

	// ---------- OnDoubleJumpEvent below

protected:
private:
};
#pragma pack(pop)
