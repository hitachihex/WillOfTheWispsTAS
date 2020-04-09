#include "stdafx.h"
#include "GameController.h"
#include "GUI.h"
#include "PlaybackManager.h"

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
	Rect r(120.0f, 139.0f, 1920.0f, 1080.0f);
	if (!originalOnce)
	{
		originalOnce = true;
		orig_GameController_OnGUI();

		// this need to set something up?
		GUI_Label(&r, g_pGUIString);
	}

	if (g_pPlaybackManager && g_bShowOSD)
	{
		String::Clear(g_pGUIString);
		mbstowcs(g_pGUIString->m_wszBytes, g_pPlaybackManager->m_szCurrentManagerState, 512 * 4);
		String::Recalcuate(g_pGUIString);
		//CreateLabelledText(&r, g_pGUIString);
		CreateLabelledTextWithSize(&r, g_pGUIString, 32);
	}
	
}