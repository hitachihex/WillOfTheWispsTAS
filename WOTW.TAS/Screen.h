#pragma once

//.data:00007FFF11E417F8 unityplayer.dll:$15D17F8 #0
#define UNITYPLAYER_SCREENINSTANCE_RVA 0x15D17F8

#pragma pack(push, 1)

class Screen
{
public:

	// 0x0000 - 0x0083
	unsigned char uc_Unk0000_0083[0x84];

	// 0x0084 - 0x0087
	int Width;

	// 0x0088 - 0x008B
	unsigned long m_dwUnk0088_008B;

	// 0x008C - 0x008F
	unsigned long m_dwUnk008C_008F;

	// 0x0090 - 0x0093
	int Height;
protected:
private:

};
#pragma pack(pop)

extern unsigned long long g_qwScreenInstancePtr;

extern Screen * GetScreenInstance();