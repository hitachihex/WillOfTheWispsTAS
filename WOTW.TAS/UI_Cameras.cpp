#include "stdafx.h"
#include "UI_Cameras.h"

unsigned long long gqw_UICamerasInstancePtr = 0x0;


inline UI_Cameras * GetCameras()
{
	// 
	unsigned long long rax = *(unsigned long long*)(gqw_UICamerasInstancePtr);
	rax = *(unsigned long long*)(rax + 0xB8);

	return (UI_Cameras*)(rax);
}