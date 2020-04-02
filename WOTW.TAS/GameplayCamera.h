#pragma once

#include "CameraController.h"
#pragma pack(push, 1)

typedef struct t_GameplayCamera
{
public:
	// 0x0000 - 0x0027
	unsigned char uc_Unk0000_0027[0x28];

	// 0x28 - 0x2F
	CameraController * m_pCameraController;
protected:
private:
} GameplayCamera;
#pragma pack(pop)
