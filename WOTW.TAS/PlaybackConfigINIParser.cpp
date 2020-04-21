#include "stdafx.h"
#include "PlaybackConfigINIParser.h"

PlaybackConfigINIParser::PlaybackConfigINIParser() : IniParser(L"PlaybackConfig.ini")
{
	this->m_RuntoSpeed.Set(L"PlaybackSettings", L"RuntoSpeed", L"300");
	this->m_Timescale.Set(L"PlaybackSettings", L"Timescale", L"1.0");

	if (!this->m_bFileExists)
		this->CreateDefault();

	this->LoadAllMappedValues();
}

bool PlaybackConfigINIParser::UpdateSettingIntoMap(std::wstring s, std::wstring k, std::wstring v)
{
	this->m_INIMap[{s, k}] = v;
	return true;
}

bool PlaybackConfigINIParser::WriteUpdatedSetting(std::wstring s, std::wstring k, std::wstring v)
{
	this->WriteKeyValue(s, k, v);

	return true;
}

void PlaybackConfigINIParser::OnSettingChanged(std::wstring s, std::wstring k, std::wstring v)
{
	this->UpdateSettingIntoMap(s, k, v);
	this->WriteUpdatedSetting(s, k, v);

	// how to propagate :think:
	// design implementation seems.. wrong
}

bool PlaybackConfigINIParser::CreateDefault()
{
	this->CreateDefaultFromMetaInfo(&this->m_RuntoSpeed);
	this->CreateDefaultFromMetaInfo(&this->m_Timescale);
	return true;
}

bool PlaybackConfigINIParser::CreateDefaultFromMetaInfo(PlaybackDefaultMetaInfo * pDefault)
{
	this->WriteKeyValue(pDefault->SectionName, pDefault->KeyName, pDefault->KeyValue);
	return true;
}

bool PlaybackConfigINIParser::LoadAllMappedValues()
{
	this->LoadSettingOrDefaultIntoMap(&this->m_RuntoSpeed);
	this->LoadSettingOrDefaultIntoMap(&this->m_Timescale);
	return true;
}

bool PlaybackConfigINIParser::LoadSettingOrDefaultIntoMap(PlaybackDefaultMetaInfo* pDefault)
{
	wchar_t * temp = this->ReadKeyValueString(pDefault->SectionName, pDefault->KeyName, pDefault->KeyValue);

	this->m_INIMap[{pDefault->SectionName, pDefault->KeyName}] = temp;
	return true;
}

std::wstring PlaybackConfigINIParser::GetSettingValue(std::wstring s, std::wstring k)
{
	return this->m_INIMap[{s, k}];
}

