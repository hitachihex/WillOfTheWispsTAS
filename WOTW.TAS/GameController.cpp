#include "stdafx.h"
#include "GameController.h"
#include "GUI.h"
#include "PlaybackManager.h"
#include "Utils.h"
#include "Screen.h"

oGameController_OnGUI orig_GameController_OnGUI = (oGameController_OnGUI)(0x0);
unsigned long long gqw_GameControllerInstancePtr = 0x0;
GameController * g_pGameControllerInstance = nullptr;

inline GameController * GetGameControllerInstance()
{
	// deref 0
	unsigned long long rax = *(unsigned long long*)(gqw_GameControllerInstancePtr);

	// deref 0xB8
	rax = *(unsigned long long*)(rax + 0xB8);

	return (GameController*)(rax);
}

void __fastcall GameController_OnGUI_Hook()
{
	static bool originalOnce = false;
	Rect r(g_fCurrentOSDXPosition, g_fCurrentOSDYPosition, 1920.0f, 1080.0f);
	//Rect r2(120.0f, 450.0f, 1920.0f, 1080.0f);
	UnityEngine_Input * pUnityEngineInput = GetUnityEngine_Input();
	Vector3 mousePos(pUnityEngineInput->m_fMouseX, pUnityEngineInput->m_fMouseY);
	if (!originalOnce)
	{
		originalOnce = true;
		orig_GameController_OnGUI();
	}

	if (g_pPlaybackManager && g_bShowOSD)
	{

		// Reposition OSD
		if (GetAsyncKeyState(VK_MBUTTON) & 1)
		{
			g_fCurrentOSDXPosition = mousePos.x;
			g_fCurrentOSDYPosition = GetScreenInstance()->Height - (int)(mousePos.y);
		}

		String::Clear(g_pGUIString);
		mbstowcs(g_pGUIString->m_wszBytes, g_pPlaybackManager->m_szCurrentManagerState, 512 * 4);
		String::Recalcuate(g_pGUIString);

		CreateLabelledTextWithSize(&r, g_pGUIString, g_nOSDFontSize);

		//r.Set(45, 139.0f, 120.0f, 20.0f);
		//g_pTextAreaString = GUI_TextArea(&r, g_pTextAreaString);


	}
	
}

void __fastcall MyWindow_Delegate(int windowID)
{

}