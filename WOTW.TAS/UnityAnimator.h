#pragma once

#include "UnityPlayer.h"
#pragma pack(push, 1)

class UnityAnimator
{
public:
protected:
private:
};
#pragma pack(pop)

typedef unsigned int(__fastcall * fnUnityEngine_Animator_GetUpdateMode)(UnityAnimator*);
extern fnUnityEngine_Animator_GetUpdateMode UnityEngine_Animator_GetUpdateMode;

