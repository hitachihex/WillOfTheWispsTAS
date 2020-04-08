#pragma once
#include "CharacterState.h"
#pragma pack(push, 1)

enum EState
{
	NORMAL,
	SLIDINGLEFT,
	SLIDINGRIGHT
};

class SeinWallSlide : CharacterState
{
public:

	// 0x00 - 0x7F = CharacterState members

	// 0x80 - 0x83
	EState CurrentState;

	// 0x84 - 0x87
	float GravityMultiplier;

	// 0x88 - 0x8B
	float InputLockDuration;

	// 0x8C - 0x8F
	float MaxFallSpeed;

	// 0x90 - 0x97
	unsigned long long MaterialBasedSeinEffectsMap_SeinEffects;

	// 0x98 - 0x9B
	float WallSlideUpAnimationMinimumSpeed;

	// 0x9C - 0x9F
	float m_inputLockTimeRemaining;

	// 0xA0 - 0xA7
	unsigned long long SoundPlayer_m_wallSlideUpSound;

	// 0xA8 - 0xAF
	unsigned long long WwiseEventSystem_SoundHandle_m_wallSlideUpSoundHandle;

	// 0xB0 - 0xB7
	unsigned long long m_qwUnk00B0_00B7;

	// 0xB8 - 0xBF
	unsigned long long m_qwUnk00B8_00BF;
	
	// 0xC0 - 0xC3
	float m_lastWallSlideDownSoundTime;

	// 0xC4 - 0xC7
	float m_minimumSoundDelay;

	// 0xC8 - 0xCF
	unsigned long long WwiseEventSystem_SoundHandle__wallSlideDownHandle;

	// 0xD0 - 0xD7
	unsigned long long m_qwUnk00D0_00D7;

	// 0xD8 - 0xDF
	unsigned long long m_qwUnk00D8_00DF;

	// 0xE0 - 0xE7
	unsigned long long IActivateAnimation_m_lastAnim;
	
protected:
private:

};
#pragma pack(pop)