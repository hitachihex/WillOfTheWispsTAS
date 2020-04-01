#pragma once

#include "Vector2.h"
#include "Vector3.h"

#define INSTANTLOADSCENESCONTROLLER_GETSCENESMANAGER_NEWPATCH_RVA 0x46B630
#define INSTANTLOADSCENESCONTROLLER_OFFSET_TO_SM_PTR              0x65        

#define SCENESMANAGER_ISPOSITIONINSIDESCENESTILLLOADING_NEWPATCH_RVA 0x16B1810
#pragma pack(push, 1)

typedef struct t_ScenesManager
{
public:

	// 0x0000 - 0x0183
	unsigned char uc_Unk0000_00183[0x184];

	// 0x184 - 0x18B
	Vector2 m_CurrentCameraTargetPosition;
protected:
private:
} ScenesManager;
#pragma pack(pop)

extern unsigned long long gqw_ScenesManagerInstancePtr;
extern ScenesManager * g_pScenesManager;

extern inline ScenesManager * GetScenesManagerInstance();

typedef bool(__fastcall * fnScenesManager_IsPositionInsideSceneStillLoading)(ScenesManager*, Vector3*);
extern fnScenesManager_IsPositionInsideSceneStillLoading ScenesManager_IsPositionInsideSceneStillLoading;
