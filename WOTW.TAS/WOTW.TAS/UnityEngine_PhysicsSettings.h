#pragma once

#pragma pack(push, 1)

typedef struct t_UnityEngine_PhysicsSettings
{
	// 0x00 - 0x47
	unsigned char uc_Unk0000_0047[0x48];

	// 0x48 - 0x4B
	float m_fFixedDeltaTime;

	// 0x4C - 0xD3
	unsigned char uc_Unk004C_00D3[0xD4 - 0x4C];

	// 0xD4 - 0xD7
	unsigned int m_CaptureFramerate;
} UnityEngine_PhysicsSettings;
#pragma pack(pop)
