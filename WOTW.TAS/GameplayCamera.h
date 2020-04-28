#pragma once

#include "CameraController.h"
#include "MonoBehaviour.h"
#pragma pack(push, 1)

class GameplayCamera : public MonoBehaviour
{
public:
	// 0x0000 - 0x0017 - MonoBehaviour members

	// 0x0018 - 0x0027
	unsigned char m_ucUnk0018_0027[0x28 - 0x18];

	// 0x28 - 0x2F
	CameraController * m_pCameraController;
protected:
private:
};
#pragma pack(pop)
