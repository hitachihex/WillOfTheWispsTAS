#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "EverythingNeedsMe.h"

//.data:00007FFF0AC8C748 gameassembly.dll:$43CC748 #0
#define GAMEASSEMBLY_UNITYEVENT_CURRENT_RVA 0x43CC748

enum EEventType : unsigned int
{
	MOUSEDOWN=0,
	MOUSEUP=1,
	MOUSEMOVE=2,
	MOUSEDRAG=3,
	KEYDOWN=4,
	KEYUP=5,
	SCROLLWHEEL=6,
	REPAINT=7,
	LAYOUT=8,
	DRAGUPDATED=9,
	DRAGPERFORM=10,
	EIGNORE=11,
	USED=12,
	VALIDATECOMMAND=13,
	EXECUTECOMAND=14,
	DRAGEXITED = 15,
	CONTEXTCLICK=16,
	MOUSEENTERWINDOW=20,
	MOUSELEAVEWINDOW=21,
	TOUCHDOWN=30,
	TOUCHUP=31,
	TOUCHMOVE=32,
	TOUCHENTER=33,
	TOUCHLEAVE=34,
	TOUCHSTATIONARY=35
};

enum EEventModifiers : unsigned int
{
	NONE=0,
	SHIFT=1,
	CONTROL=2,
	ALT=4,
	COMMAND=8,
	NUMERIC=16,
	CAPSLOCK=32,
	FUNCTIONKEY=64
};

#pragma pack(push, 1)

class UnityEvent_Internal
{
public:

	// 0x0000 - 0x0003
	EEventType m_Type;

	// 0x0004 - 0x0017
	unsigned char uc_Unk0004_0029[0x18 - 0x04];

	// 0x0018 - 0x001B
	int m_MouseButton;

	// 0x001C - 0x001F
	EEventModifiers m_Modifiers;

	// 0x0020 - 0x0023
	float m_Pressure;

	// 0x0024 - 0x0027
	unsigned int m_ClickCount;

	// 0x0028 - 0x0029
	unsigned short m_Character;

	// 0x002A - 0x002B
	unsigned short m_Keycode;

	// 0x002C - 0x002F
	unsigned int m_DisplayIndex;
protected:
private:
};

class UnityEvent
{
public:

	// 0x0000 - 0x0007
	unsigned long long m_qwUnk0000_0007;

	// 0x0008 - 0x000F
	unsigned long long m_qwUnk0008_000F;

	// 0x0010 - 0x0017
	UnityEvent_Internal * m_pInternal;
protected:
private:
};
#pragma pack(pop)


extern unsigned long long g_qwUnityEventCurrent_InstancePtr;

extern UnityEvent * GetCurrentEventInstance();