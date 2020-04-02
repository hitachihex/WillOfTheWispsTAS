#pragma once
#pragma pack(push, 1)

#include "Vector2.h"
typedef struct t_Core_Input
{
public:

	// 0x00 - 0x03
	float Horizontal;

	// 0x04 - 0x07
	float Vertical;

	// 0x08 - 0x0B
	float HorizontalMenu;

	// 0x0C - 0xF
	float VerticalMenu;

	// 0x10 - 0x13
	int HorizontalDigiPad;

	// 0x14 - 0x17
	int VerticalDigiPad;

	// 0x18 - 0x1B
	int HorizontalKey;

	// 0x1C - 0x1F
	int VerticalKey;

	// 0x20 - 0x23
	float HorizontalAnalogLeft;

	// 0x24 - 0x27
	float VerticalAnalogLeft;

	// 0x28 - 0x2B
	float HorizontalAnalogRight;

	// 0x2C - 0x2F
	float VerticalAnalogRight;

	// 0x30 - 0x33
	float LeftTriggerAxis;
	
	// 0x34 - 0x37
	float RightTriggerAxis;

	// 0x38 - 0x3F
	Vector2 CursorPosition;

	// 0x40 
	bool CursorMoved;

	// 0x41
	bool m_b0041;

	// 0x42
	bool m_b0042;

	// 0x43
	bool m_b0043;

	// 0x44
	bool m_b0044;

	// 0x45
	bool m_b045;

	// 0x46
	bool m_b046;

	// 0x47
	bool m_b047;

protected:
private:
} Core_Input;

#pragma pack(pop)

extern unsigned long long gqw_CoreInputInstancePtr;
extern inline Core_Input * GetCoreInputInstance();

