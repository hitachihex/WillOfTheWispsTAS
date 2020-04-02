#pragma once
#include "Vector2.h"

#pragma pack(push, 1)

#define INSTANTLOADSCENESCONTROLLER_AWAKE_NEWPATCH_RVA 0x46B4C0
#define INSTANTLOADSCENESCONTROLLER_OFFSET_TO_PTR      0x6B
typedef struct t_InstantLoadScenesController
{
public:
	// 0x00 - 0x1F
	unsigned char uc_Unk0000_0017[0x20];

	// 0x20
	bool m_IsLoading;

	// 0x21
	bool m_b0021;

	// 0x22
	bool m_b0022;

	// 0x23
	bool m_b0023;

	// 0x24 - 0x27
	float m_startInstantlyLoadingScenesTime;

	// 0x28
	bool m_bEntireGameFrozen;

	// 0x29
	bool m_b0029;

	// 0x2A
	bool m_b002A;

	// 0x2B
	bool m_b002B;

	// ...
protected:
private:
} InstantLoadScenesController;
#pragma pack(pop)

extern unsigned long long gqw_InstantLoadScenesControllerInstancePtr;
extern InstantLoadScenesController * g_pInstantLoadScenesControllerInstance;

typedef void(__fastcall * oInstantLoadScenesController_CompleteLoading)(InstantLoadScenesController*);
extern oInstantLoadScenesController_CompleteLoading original_InstantLoadScenesController_CompleteLoading;
extern void __fastcall InstantLoadScenesController_CompleteLoading_Hook(InstantLoadScenesController*);

extern inline InstantLoadScenesController * GetInstanceLoadScenesControllerInstance();