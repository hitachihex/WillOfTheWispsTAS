#pragma once

#include "IniParser.h"
#include <sstream>

typedef struct t_PlaybackDefaultMetaInfo
{
public:
	std::wstring SectionName;
	std::wstring KeyName;
	std::wstring KeyValue;

	inline void Set(std::wstring sName, std::wstring kName, std::wstring kVal)
	{
		this->SectionName = sName;
		this->KeyName = kName;
		this->KeyValue = kVal;
	}

protected:
private:
}PlaybackDefaultMetaInfo;

class PlaybackConfigINIParser : public IniParser
{
public:
	PlaybackConfigINIParser();

	bool CreateDefaultFromMetaInfo(PlaybackDefaultMetaInfo*);
	bool CreateDefault();

	bool LoadSettingOrDefaultIntoMap(PlaybackDefaultMetaInfo*);
	bool LoadAllMappedValues();

	bool UpdateSettingIntoMap(std::wstring, std::wstring, std::wstring);
	bool WriteUpdatedSetting(std::wstring, std::wstring, std::wstring);

	std::wstring GetSettingValue(std::wstring, std::wstring);
	void OnSettingChanged(std::wstring, std::wstring, std::wstring);

	template<typename T>
	T SettingFromMap(std::wstring sName, std::wstring kName)
	{
		const std::wstring& keyValue = this->m_INIMap[{sName, kName}];

		if (!keyValue.empty())
		{
			std::wstringstream wss(keyValue);
			T result;
			wss >> result;

			if (wss.fail()) return T();
			return result;
		}
		return T();
	}

	PlaybackDefaultMetaInfo m_RuntoSpeed;
	PlaybackDefaultMetaInfo m_Timescale;
protected:
private:
};