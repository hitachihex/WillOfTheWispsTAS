#include "stdafx.h"
#include "ConfigurationManager.h"

ConfigurationManager * g_pConfigManager = new ConfigurationManager();

bool IsAnyModifierKey(unsigned short uKc)
{
	bool isModifier = false;
	switch (uKc)
	{
	//case UKC::LeftShift:
	//case UKC::RightShift:
	case UKC::LeftCtrl:
	case UKC::RightCtrl:
	case UKC::LeftAlt:
	case UKC::RightAlt:
		isModifier = true;
		break;

	}

	return isModifier;
}

void ConfigurationManager::UpdateKeybind(ButtonKey* pButtonKey)
{
	std::wstring sName = L"";
	switch (pButtonKey->m_nIndex)
	{
	case FRAMESTEP_INDEX:
		sName = L"Framestep";
		break;
	case PAUSE_INDEX:
		sName = L"Pause";
		break;
	case PLAYBACK_INDEX:
		sName = L"Playback";
		break;
	case SHOWCONFIG_INDEX:
		sName = L"ShowConfig";
		break;
	case MOVEOSD_INDEX:
		sName = L"MoveOSD";
		break;
	case SHOWOSD_INDEX:
		sName = L"ShowOSD";
		break;
	case COPYCURSOR_INDEX:
		sName = L"CopyCursor";
		break;
	case COPYPOSITION_INDEX:
		sName = L"CopyPos";
		break;
	case COPYSPEED_INDEX:
		sName = L"CopySpeed";
		break;
	default:
		return;
		break;
	}

	this->m_pKeybindParser->UpdateKeybindIntoMap(sName, pButtonKey->GetKey()->uUnityKeycode, pButtonKey->m_bTransitiveShift,
		pButtonKey->m_bTransitiveCtrl, pButtonKey->m_bTransitiveAlt);

	this->m_pKeybindParser->WriteUpdatedKeybind(sName);
}