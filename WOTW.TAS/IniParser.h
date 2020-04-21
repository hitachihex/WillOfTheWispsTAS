#pragma once

#include <Windows.h>
#include <wchar.h>
#include <string>
#include <map>
#include <vector>

class IniParser
{
public:

	IniParser(std::wstring);

	// methods
	std::wstring GetFilePath();

	std::wstring GetFileName();

	// fields
	std::wstring m_CWD;

	std::map<std::pair<std::wstring, std::wstring>, std::wstring> GetMap();

	virtual bool CreateDefault() = 0;

	virtual bool LoadAllMappedValues() = 0;

	//std::wstring ReadKeyValueString(std::wstring, std::wstring, std::wstring);
	unsigned int ReadKeyValueUINT(std::wstring, std::wstring, unsigned int);
	void ReadKeyValueString(std::wstring, std::wstring, std::wstring);
	bool WriteKeyValue(std::wstring, std::wstring, std::wstring);
protected:
	// SectionName, KeyName, Value
	FILE * m_Fp;
	std::map<std::pair<std::wstring, std::wstring>, std::wstring> m_INIMap;
	std::wstring m_FilePath;
	std::wstring m_FileName;

	bool m_bFileExists;
	wchar_t m_szCurrentDirectory[512];
private:

};

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

	PlaybackDefaultMetaInfo m_RuntoSpeed;
	PlaybackDefaultMetaInfo m_Timescale;
protected:
private:
};

typedef struct t_KeybindDefaultMetaInfo
{
public:
	std::wstring SectionName;
	unsigned int Keycode;
	bool bShift;
	bool bCtrl;
	bool bAlt;

	inline void Set(std::wstring sName, unsigned int nKeycode, bool shift, bool ctrl, bool alt)
	{
		this->SectionName = sName;
		this->Keycode = nKeycode;
		this->bShift = shift;
		this->bCtrl = ctrl;
		this->bAlt = alt;
	}
protected:
private:
} KeybindDefaultMetaInfo;

class KeybindINIParser : public IniParser
{
public:
	KeybindINIParser();

	bool CreateDefaultFromMetaInfo(KeybindDefaultMetaInfo*);
	bool CreateDefault();

	bool LoadKeybindIntoMap(KeybindDefaultMetaInfo*);
	bool LoadAllMappedValues();


	unsigned int GetKeycode(std::wstring);
	bool GetIsShift(std::wstring);
	bool GetIsCtrl(std::wstring);
	bool GetIsAlt(std::wstring);
	//unsigned short GetKeycode();

	void WriteUpdatedKeybind(std::wstring);
	void UpdateKeybindIntoMap(std::wstring, unsigned short, bool, bool, bool);
	KeybindDefaultMetaInfo m_FramestepDefault;
	KeybindDefaultMetaInfo m_PauseDefault;
	KeybindDefaultMetaInfo m_PlaybackDefault;
	KeybindDefaultMetaInfo m_ShowConfigDefault;
	KeybindDefaultMetaInfo m_ShowOSDDefault;
	KeybindDefaultMetaInfo m_MoveOSDDefault;
	KeybindDefaultMetaInfo m_CopyCursorDefault;
	KeybindDefaultMetaInfo m_CopyPosDefault;
	KeybindDefaultMetaInfo m_CopySpeedDefault;
protected:
private:
};