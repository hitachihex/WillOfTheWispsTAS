#pragma once

#define UNITYPLAYER_GETMOUSEBUTTONUP_RVA 0x929160
#pragma pack(push, 1)
typedef struct t_UnityEngine_Input
{

	// (this isn't called UnityEngine_Input)
	// 0xA8 = deltaTime.
	// 0x0000 - 0x00BF
	unsigned char uc_Unk0000_00BF[0xC0];

	// 0xC0 - 0xC3
	float m_fMouseX;

	// 0xC4 - 0xC7
	float m_fMouseY;
	
}UnityEngine_Input;
#pragma pack(pop)

typedef bool(__fastcall * fnUnityEngine_Input_GetMouseButtonUp)(int);
extern fnUnityEngine_Input_GetMouseButtonUp Input_GetMouseButtonUp;
