#include "stdafx.h"
#include "IniParser.h"
#include "EasyHookUtils.h"


IniParser::IniParser(std::wstring configFileName)
{
	this->m_bFileExists = false;
	this->m_Fp = nullptr;
	auto nLen = GetModuleFileNameW(nullptr, this->m_szCurrentDirectory, 512);
	this->m_CWD.assign(this->m_szCurrentDirectory);

	auto indexOfLastBackslash = this->m_CWD.rfind(L"\\");
	this->m_CWD.erase(indexOfLastBackslash + 1, this->m_CWD.length() - indexOfLastBackslash + 1);
	
	this->m_CWD += L"\\";
	this->m_FilePath = this->m_CWD;
	this->m_FileName = this->m_FilePath;
	this->m_FileName += configFileName;

	// alright, if we have a null file pointer then we should default everything.
	this->m_Fp = _wfsopen(this->m_FileName.c_str(), L"r", _SH_DENYNO);

	if (this->m_Fp == nullptr)
	{
	
		// create the file because it doesn't exist
		this->m_Fp = _wfsopen(this->m_FileName.c_str(), L"a", _SH_DENYNO);
		
		// close it..
		fclose(this->m_Fp);

		// drop the handle
		this->m_Fp = nullptr;

		// let derived know
		this->m_bFileExists = false;
	}
	else
	{
		// let derived know
		this->m_bFileExists = true;

		// it existed, just close it
		fclose(this->m_Fp);

		// then drop the handle
		this->m_Fp = nullptr;
	}
}

std::map<std::pair<std::wstring, std::wstring>, std::wstring> IniParser::GetMap()
{
	return this->m_INIMap;
}

std::wstring IniParser::GetFilePath()
{
	return this->m_FilePath;
}

std::wstring IniParser::GetFileName()
{
	return this->m_FileName;
}
bool IniParser::WriteKeyValue(std::wstring sectionName, std::wstring keyName, std::wstring value)
{
	return WritePrivateProfileStringW(sectionName.c_str(), keyName.c_str(), value.c_str(), this->m_FileName.c_str());
}

unsigned int IniParser::ReadKeyValueUINT(std::wstring sectionName, std::wstring keyName, unsigned int defaultValue)
{
	return GetPrivateProfileIntW(sectionName.c_str(), keyName.c_str(), defaultValue, this->m_FileName.c_str());
}

void IniParser::ReadKeyValueString(std::wstring sectionName, std::wstring keyName, std::wstring c)
{
	return;
	//GetPrivateProfileStringW(sectionName, keyName,)
}

/*PlaybackConfigINIParser();
	bool CreateDefault();
	bool LoadAllMappedValues();*/

PlaybackConfigINIParser::PlaybackConfigINIParser() : IniParser(L"PlaybackConfig.ini")
{
	this->m_RuntoSpeed.Set(L"PlaybackSettings", L"RuntoSpeed", L"300");
	this->m_Timescale.Set(L"PlaybackSettings", L"Timescale", L"1.0");

	if (!this->m_bFileExists)
		this->CreateDefault();

	this->LoadAllMappedValues();
}
// ----------
KeybindINIParser::KeybindINIParser() : IniParser(L"Config.ini")
{
	this->m_FramestepDefault.Set(L"Framestep", 91, false, false, false);
	this->m_PauseDefault.Set(L"Pause", 282, false, false, false);
	this->m_PlaybackDefault.Set(L"Playback", 285, false, false, false);
	this->m_ShowConfigDefault.Set(L"ShowConfig", 289, false, false, false);
	this->m_ShowOSDDefault.Set(L"ShowOSD", 290, false, false, false);

	this->m_MoveOSDDefault.Set(L"MoveOSD", 1, false, true, false);
	this->m_CopyCursorDefault.Set(L"CopyCursor", 257, false, true, false);
	this->m_CopyPosDefault.Set(L"CopyPos", 258, false, true, false);
	this->m_CopySpeedDefault.Set(L"CopySpeed", 259, false, true, false);

	if(!this->m_bFileExists)
		this->CreateDefault();

	this->LoadAllMappedValues();

}

unsigned int KeybindINIParser::GetKeycode(std::wstring sectionName)
{
	return std::stoul(this->m_INIMap[{sectionName, L"UnityKeycode"}]);
}

bool KeybindINIParser::GetIsShift(std::wstring sectionName)
{
	return (bool)(std::stoul(this->m_INIMap[{sectionName, L"Shift"}]));
}
bool KeybindINIParser::GetIsCtrl(std::wstring sectionName)
{
	return (bool)(std::stoul(this->m_INIMap[{sectionName, L"Ctrl"}]));
}
bool KeybindINIParser::GetIsAlt(std::wstring sectionName)
{
	return (bool)(std::stoul(this->m_INIMap[{sectionName, L"Alt"}]));
}

bool PlaybackConfigINIParser::LoadSettingOrDefaultIntoMap(PlaybackDefaultMetaInfo* pDefault)
{
	return true;
}

bool KeybindINIParser::LoadKeybindIntoMap(KeybindDefaultMetaInfo* pDefaults)
{
	std::wstring temp = L"";
	unsigned int Keycode = this->ReadKeyValueUINT(pDefaults->SectionName, L"UnityKeycode", pDefaults->Keycode);
	bool isShift = (bool)this->ReadKeyValueUINT(pDefaults->SectionName, L"Shift", (unsigned int)pDefaults->bShift);
	bool isCtrl = (bool)this->ReadKeyValueUINT(pDefaults->SectionName, L"Ctrl", (unsigned int)pDefaults->bCtrl);
	bool isAlt = (bool)this->ReadKeyValueUINT(pDefaults->SectionName, L"Alt", (unsigned int)pDefaults->bAlt);

	temp = std::to_wstring(Keycode);
	this->m_INIMap[{pDefaults->SectionName, L"UnityKeycode"}] = temp;
	//DebugOutputW(L"KeybindINIParser::LoadKeybindIntoMap: [%s,UnityKeycode]=%u", pDefaults->SectionName.c_str(), Keycode);
	temp = std::to_wstring(isShift);
	this->m_INIMap[{pDefaults->SectionName, L"Shift"}] = temp;
	temp = std::to_wstring(isCtrl);
	this->m_INIMap[{pDefaults->SectionName, L"Ctrl"}] = temp;
	temp = std::to_wstring(isAlt);
	this->m_INIMap[{pDefaults->SectionName, L"Alt"}] = temp;

	return true;
}

void KeybindINIParser::UpdateKeybindIntoMap(std::wstring sectionName, unsigned short uKeycode, bool bShift, bool bCtrl, bool bAlt)
{
	this->m_INIMap[{sectionName, L"UnityKeycode"}] = std::to_wstring(uKeycode);
	this->m_INIMap[{sectionName, L"Shift"}] = std::to_wstring(bShift);
	this->m_INIMap[{sectionName, L"Ctrl"}] = std::to_wstring(bCtrl);
	this->m_INIMap[{sectionName, L"Alt"}] = std::to_wstring(bAlt);
}

void KeybindINIParser::WriteUpdatedKeybind(std::wstring sectionName)
{
	// pull from the map
	this->WriteKeyValue(sectionName, L"UnityKeycode", this->m_INIMap[{sectionName, L"UnityKeycode"}]);
	this->WriteKeyValue(sectionName, L"Shift", this->m_INIMap[{sectionName, L"Shift"}]);
	this->WriteKeyValue(sectionName, L"Ctrl", this->m_INIMap[{sectionName, L"Ctrl"}]);
	this->WriteKeyValue(sectionName, L"Alt", this->m_INIMap[{sectionName, L"Alt"}]);
}

bool KeybindINIParser::LoadAllMappedValues()
{
	this->LoadKeybindIntoMap(&this->m_FramestepDefault);
	this->LoadKeybindIntoMap(&this->m_PauseDefault);
	this->LoadKeybindIntoMap(&this->m_PlaybackDefault);
	this->LoadKeybindIntoMap(&this->m_ShowConfigDefault);
	this->LoadKeybindIntoMap(&this->m_ShowOSDDefault);
	this->LoadKeybindIntoMap(&this->m_MoveOSDDefault);
	this->LoadKeybindIntoMap(&this->m_CopyCursorDefault);
	this->LoadKeybindIntoMap(&this->m_CopyPosDefault);
	this->LoadKeybindIntoMap(&this->m_CopySpeedDefault);

	return true;
}

bool PlaybackConfigINIParser::LoadAllMappedValues()
{
	return true;
}

bool PlaybackConfigINIParser::CreateDefaultFromMetaInfo(PlaybackDefaultMetaInfo * pDefault)
{
	this->WriteKeyValue(pDefault->SectionName, pDefault->KeyName, pDefault->KeyValue);
	return true;
}

bool KeybindINIParser::CreateDefaultFromMetaInfo(KeybindDefaultMetaInfo* pDefault)
{

	this->WriteKeyValue(pDefault->SectionName, L"UnityKeycode", std::to_wstring(pDefault->Keycode));
	this->WriteKeyValue(pDefault->SectionName, L"Shift", std::to_wstring(pDefault->bShift));
	this->WriteKeyValue(pDefault->SectionName, L"Ctrl", std::to_wstring(pDefault->bCtrl));
	this->WriteKeyValue(pDefault->SectionName, L"Alt", std::to_wstring(pDefault->bAlt));

	return true;
}

bool PlaybackConfigINIParser::CreateDefault()
{
	this->CreateDefaultFromMetaInfo(&this->m_RuntoSpeed);
	this->CreateDefaultFromMetaInfo(&this->m_Timescale);
	return true;
}

bool KeybindINIParser::CreateDefault()
{
	this->CreateDefaultFromMetaInfo(&this->m_FramestepDefault);
	this->CreateDefaultFromMetaInfo(&this->m_PauseDefault);
	this->CreateDefaultFromMetaInfo(&this->m_PlaybackDefault);
	this->CreateDefaultFromMetaInfo(&this->m_ShowConfigDefault);
	this->CreateDefaultFromMetaInfo(&this->m_ShowOSDDefault);
	this->CreateDefaultFromMetaInfo(&this->m_MoveOSDDefault);
	this->CreateDefaultFromMetaInfo(&this->m_CopyCursorDefault);
	this->CreateDefaultFromMetaInfo(&this->m_CopyPosDefault);
	this->CreateDefaultFromMetaInfo(&this->m_CopySpeedDefault);

	/*
	this->WriteKeyValue(L"Framestep", L"UnityKeycode", L"91");
	this->WriteKeyValue(L"Framestep", L"Shift", L"0");
	this->WriteKeyValue(L"Framestep", L"Ctrl", L"0");
	this->WriteKeyValue(L"Framestep", L"Alt", L"0");

	this->WriteKeyValue(L"Pause", L"UnityKeycode", L"282");
	this->WriteKeyValue(L"Pause", L"Shift", L"0");
	this->WriteKeyValue(L"Pause", L"Ctrl", L"0");
	this->WriteKeyValue(L"Pause", L"Alt", L"0");

	this->WriteKeyValue(L"Playback", L"UnityKeycode", L"285");
	this->WriteKeyValue(L"Playback", L"Shift", L"0");
	this->WriteKeyValue(L"Playback", L"Ctrl", L"0");
	this->WriteKeyValue(L"Playback", L"Alt", L"0");

	this->WriteKeyValue(L"ShowConfig", L"UnityKeycode", L"289");
	this->WriteKeyValue(L"ShowConfig", L"Shift", L"0");
	this->WriteKeyValue(L"ShowConfig", L"Ctrl", L"0");
	this->WriteKeyValue(L"ShowConfig", L"Alt", L"0");

	this->WriteKeyValue(L"ShowOSD", L"UnityKeycode", L"290");
	this->WriteKeyValue(L"ShowOSD", L"Shift", L"0");
	this->WriteKeyValue(L"ShowOSD", L"Ctrl", L"0");
	this->WriteKeyValue(L"ShowOSD", L"Alt", L"0");

	this->WriteKeyValue(L"MoveOSD", L"UnityKeycode", L"1");
	this->WriteKeyValue(L"MoveOSD", L"Shift", L"0");
	this->WriteKeyValue(L"MoveOSD", L"Ctrl", L"1");
	this->WriteKeyValue(L"MoveOSD", L"Alt", L"0");

	this->WriteKeyValue(L"CopyCursor", L"UnityKeycode", L"257");
	this->WriteKeyValue(L"CopyCursor", L"Shift", L"0");
	this->WriteKeyValue(L"CopyCursor", L"Ctrl", L"1");
	this->WriteKeyValue(L"CopyCursor", L"Alt", L"0");

	this->WriteKeyValue(L"CopyPos", L"UnityKeycode", L"258");
	this->WriteKeyValue(L"CopyPos", L"Shift", L"0");
	this->WriteKeyValue(L"CopyPos", L"Ctrl", L"1");
	this->WriteKeyValue(L"CopyPos", L"Alt", L"0");

	this->WriteKeyValue(L"CopySpeed", L"UnityKeycode", L"259");
	this->WriteKeyValue(L"CopySpeed", L"Shift", L"0");
	this->WriteKeyValue(L"CopySpeed", L"Ctrl", L"1");
	this->WriteKeyValue(L"CopySpeed", L"Alt", L"0");*/

	return true;
}