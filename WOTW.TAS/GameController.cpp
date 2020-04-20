#include "stdafx.h"
#include "GameController.h"
#include "GUI.h"
#include "PlaybackManager.h"
#include "Utils.h"
#include "Screen.h"
#include "UnityEngineEvent.h"
#include "UnityButton.h"
#include "UnityTextArea.h"
#include "ConfigurationManager.h"

oGameController_OnGUI orig_GameController_OnGUI = (oGameController_OnGUI)(0x0);
oGameController_Update orig_GameController_Update = (oGameController_Update)(0x0);
unsigned long long gqw_GameControllerInstancePtr = 0x0;
GameController * g_pGameControllerInstance = nullptr;
wchar_t g_tempBuffer[512 * 4] = { 0 };

//UnityButton * g_pTestButton = new UnityButton(L"Framestep:", 45.0f, 139.0f, 160.0f, 45.0f);
//UnityTextArea * g_pTestTextArea = new UnityTextArea(Framestep->pcszCharacter, 45.0f + 162.0f, 139.0f, 130.0f, 40.0f, false);
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
	static bool bShiftDown = false;
	static bool bCtrlDown = false;
	static bool bAltDown = false;

	Rect r(g_fCurrentOSDXPosition, g_fCurrentOSDYPosition, 1920.0f, 1080.0f);
	UnityEngine_Input * pUnityEngineInput = GetUnityEngine_Input();
	Vector3 mousePos(pUnityEngineInput->m_fMouseX, pUnityEngineInput->m_fMouseY);
	if (!originalOnce)
	{
		originalOnce = true;
		orig_GameController_OnGUI();
		return;
	}

	if (g_pPlaybackManager && g_bShowOSD)
	{
		if (g_pConfigManager->ValidTimeToCheckKey())
		{
			if (g_pConfigManager->MoveOSD->CheckKey(true))
			{
				g_fCurrentOSDXPosition = mousePos.x;
				g_fCurrentOSDYPosition = GetScreenInstance()->Height - (int)(mousePos.y);
			}
		}

		String::Clear(g_pGUIString);
		mbstowcs(g_pGUIString->m_wszBytes, g_pPlaybackManager->m_szCurrentManagerState, 512 * 4);
		String::Recalcuate(g_pGUIString);

		CreateLabelledTextWithSize(&r, g_pGUIString, g_nOSDFontSize);
	}


	// NOTE: Don't let the menu just disappear if they've hit the menu toggle key while changing a key.
	// Also, let the timer tick a bit before it checks the toggle config key based on WasAnyJustSet :)
	// The problem is the key is getting set almost instantly, and then it's returning true on the keycheck.
	if (g_pConfigManager->ValidTimeToCheckKey())
	{
		if (g_pConfigManager->ToggleConfigActive->CheckKey(true))
		{
			g_pConfigManager->m_bKeybindsMenuActive = !g_pConfigManager->m_bKeybindsMenuActive;

			// if we toggled to true, deactivate all our shit.
			if (g_pConfigManager->m_bKeybindsMenuActive)
				g_pConfigManager->DeactivateAll();
		}
	}

	// Don't check if we don't care to show the menu.
	if (!g_pConfigManager->m_bKeybindsMenuActive)
		return;

	auto pCurrentEvent = GetCurrentEventInstance();

	g_pConfigManager->UpdateButtonGUIStates();
	g_pConfigManager->UpdateTextAreaGUIStates();

	if (pCurrentEvent)
	{
		if (pCurrentEvent->m_pInternal)
		{
			auto pButtonKey = g_pConfigManager->GetWorkingDirtyButtonKey();

			if (!pButtonKey)
				return;

			// so LCTRL\RCTRL, LALT\RALT is detected as a keydown\keyup - but not shift.
			// so shift will require checking the modifier, also don't check it inside
			// up or down events
			if (pCurrentEvent->m_pInternal->m_Modifiers & EEventModifiers::SHIFT)
			{
				bShiftDown = true;
			}

			if (pCurrentEvent->m_pInternal->m_Type == EEventType::KEYDOWN || pCurrentEvent->m_pInternal->m_Type == EEventType::MOUSEDOWN)
			{
				bool isMouseEvent = pCurrentEvent->m_pInternal->m_Type == EEventType::MOUSEDOWN;
				unsigned short keyCode = 0xFFFF;
				if (isMouseEvent)
					keyCode = pCurrentEvent->m_pInternal->m_MouseButton & 0xFFFF;
				else
					keyCode = pCurrentEvent->m_pInternal->m_Keycode;

				if (pButtonKey)
				{
					if (keyCode == UKC::UKC_Escape)
					{
						// Reset these for next time we try to change some modifiers for another key
						bAltDown = false;
						bCtrlDown = false;
						bShiftDown = false;

						// Don't update key, let the manager know we escaped out of a bind set action.
						g_pConfigManager->DeactivateAll(false, true);
						return;
					}

					auto pKey = keyMap.find(keyCode);

					if (IsAnyModifierKey(keyCode,&bCtrlDown,&bAltDown))
					{
						// lol, this looks silly, but it should be better
					}
					else
					{
						// Wasn't found, what are you pressing?
						if (pKey == keyMap.end())
						{
							bAltDown = false;
							bCtrlDown = false;
							bShiftDown = false;
							g_pConfigManager->DeactivateAll(false, true);
							return;
						}

						// we're rebinding Framestep right now, make sure it's not trying to be bound to Pause :p
						if (pButtonKey->m_nIndex == FRAMESTEP_INDEX)
						{
							auto pauseKeycode = g_pConfigManager->Pause->GetKey()->uUnityKeycode;
							if (pauseKeycode == pKey->second->uUnityKeycode)
							{
								bAltDown = false;
								bCtrlDown = false;
								bShiftDown = false;
								g_pConfigManager->DeactivateAll(false, true);

								return;
							}
						}

						// we're rebinding Pause right now, make sure it's not trying to be bound to Framestep :p
						if (pButtonKey->m_nIndex == PAUSE_INDEX)
						{
							auto framestepKeycode = g_pConfigManager->Framestep->GetKey()->uUnityKeycode;

							if (framestepKeycode == pKey->second->uUnityKeycode)
							{
								bAltDown = false;
								bCtrlDown = false;
								bShiftDown = false;
								g_pConfigManager->DeactivateAll(false, true);

								return;
							}
						}

						// Not binding Pause, see if we're trying to bind other things to what Pause is
						if (pButtonKey->m_nIndex != PAUSE_INDEX)
						{
							auto pauseKeycode = g_pConfigManager->Pause->GetKey()->uUnityKeycode;

							if (pKey->second->uUnityKeycode == pauseKeycode)
							{
								bAltDown = false;
								bCtrlDown = false;
								bShiftDown = false;
								g_pConfigManager->DeactivateAll(false, true);

								return;
							}
						}

						// Not binding Framestep, see if we're trying to bind other things to what Framestep is
						if (pButtonKey->m_nIndex != FRAMESTEP_INDEX)
						{
							auto frameStepKeycode = g_pConfigManager->Framestep->GetKey()->uUnityKeycode;
							if (pKey->second->uUnityKeycode == frameStepKeycode)
							{
								bAltDown = false;
								bCtrlDown = false;
								bShiftDown = false;
								g_pConfigManager->DeactivateAll(false, true);

								return;
							}
						}

						// Not binding ToggleConfigActive, see if we're trying to bind other things to what ToggleConfigActive is
						if (pButtonKey->m_nIndex != SHOWCONFIG_INDEX)
						{
							auto toggleConfigActiveKeycode = g_pConfigManager->ToggleConfigActive->GetKey()->uUnityKeycode;

							if (pKey->second->uUnityKeycode == toggleConfigActiveKeycode)
							{
								bAltDown = false;
								bCtrlDown = false;
								bShiftDown = false;
								g_pConfigManager->DeactivateAll(false, true);

								return;
							}
						}

						// We're binding ToggleConfigActive, see if we're trying to bind this to what other things are
						if (pButtonKey->m_nIndex == SHOWCONFIG_INDEX)
						{
							if (g_pConfigManager->CheckAnnoyingCombinations(pKey->second->uUnityKeycode))
							{
								bAltDown = false;
								bCtrlDown = false;
								bShiftDown = false;
								g_pConfigManager->DeactivateAll(false, true);

								return;
							}
						}

						/* Right now, with the way this works, you can't have a mouse
						   and a keyboard key bound together, or multi-'main' keycodes.
						   I'm sorry, I didn't feel like redoing everything after I noticed my mistake!

						   This is better than hardcoding everything, at least :)
						   */


						   // Set the modifiers
						pButtonKey->m_bTransitiveAlt = bAltDown;
						pButtonKey->m_bTransitiveCtrl = bCtrlDown;
						pButtonKey->m_bTransitiveShift = bShiftDown;

						// Set the new key.
						pButtonKey->SafeSetKey(pKey->second, true);

						// Update the keybind
						g_pConfigManager->UpdateKeybind(pButtonKey);

						// Reset these for next time we try to change some modifiers for another key
						bAltDown = false;
						bCtrlDown = false;
						bShiftDown = false;

						g_pConfigManager->DeactivateAll();

					}
				}

			}
		}
	}
}

void __fastcall GameController_Update_Hook(GameController* self)
{
	g_pConfigManager->UpdateButtonKeyTimers();
	g_pConfigManager->UpdateCurrentDirtyButtonTimer();
	return orig_GameController_Update(self);
}

void __fastcall MyWindow_Delegate(int windowID)
{

}