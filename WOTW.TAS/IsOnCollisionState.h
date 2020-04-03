#pragma once

#pragma pack(push, 1)
typedef struct t_IsOnCollisionState
{
public:

	// 0x00 - 0x0F
	unsigned char uc_Unk0000_000F[0x10];

	// 0x10
	bool WasOn;

	// 0x11
	bool IsOn;

	// 0x12
	bool FutureOn;
protected:
private:
} IsOnCollisionState;
#pragma pack(pop)