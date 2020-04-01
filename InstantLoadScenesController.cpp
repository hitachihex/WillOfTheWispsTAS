#include "stdafx.h"
#include "InstantLoadScenesController.h"

InstantLoadScenesController * g_pInstantLoadScenesControllerInstance = nullptr;


// Think it's fine, we can just get the ptr from Awake() by relative calc.
unsigned long long gqw_InstantLoadScenesControllerInstancePtr = 0x0;

/* Hmm, we have a problem, this won't get called once until CompleteLoading itself is called.
   Under this assumption.. we'd have to ignore it being null, until it wasn't null.

   Bad design.
*/
oInstantLoadScenesController_CompleteLoading original_InstantLoadScenesController_CompleteLoading = (oInstantLoadScenesController_CompleteLoading)(0x0);

void __fastcall InstantLoadScenesController_CompleteLoading_Hook(InstantLoadScenesController* rcx)
{
	g_pInstantLoadScenesControllerInstance = rcx;
}

inline InstantLoadScenesController * GetInstanceLoadScenesControllerInstance()
{
	// deref 0
	unsigned long long rax = *(unsigned long long*)(gqw_InstantLoadScenesControllerInstancePtr);

	// deref 0xB8
	unsigned long long rcx = *(unsigned long long*)(rax + 0xB8);

	// deref 0
	//rcx = *(unsigned long long*)(rcx);

	return (InstantLoadScenesController*)(rcx);
}