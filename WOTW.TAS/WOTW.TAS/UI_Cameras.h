#pragma once

#include "GameplayCamera.h"
#pragma pack(push, 1)

// Game.UI.Cameras
typedef struct t_UI_Cameras
{
	// 0x00 - 0x07
	unsigned long long CameraSystem_system;

	// 0x08 - 0x0F
	GameplayCamera * m_pCurrent;
} UI_Cameras;
#pragma pack(pop)

extern unsigned long long gqw_UICamerasInstancePtr;
extern inline UI_Cameras * GetCameras();