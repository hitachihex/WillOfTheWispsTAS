#pragma once

#include "UnityEngine_Camera.h"
#pragma pack(push, 1)

typedef struct t_CameraController
{
public:

	// 0x0000 - 0x0017
	unsigned char uc_Unk0000_0017[0x18];

	// 0x18 - 0x1F
	UnityEngine_Camera * m_pCamera;
protected:
private:
} CameraController;
#pragma pack(pop)