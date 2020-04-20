#pragma once
#include <WinUser.h>
#include <map>
#include "String.h"
#include "UnityButton.h"
#include "UnityTextArea.h"
#include "IniParser.h"
#include <vector>
#include <math.h>

static constexpr float g_fDefButtonHeight = 40.0f;
static constexpr float g_fDefButtonWidth = 100.0f;
static constexpr float g_fDefButtonXPos = 45.0f;
static constexpr float g_fDefButtonYPos = 139.0f;

static constexpr float g_fDefTAHeight = 40.0f;
static constexpr float g_fDefTAWidth = 100.0f;
static constexpr float g_fDefTAXPos = 45.0f + g_fDefButtonWidth + 2.0f;
static constexpr float g_fDefTAYPos = 139.0f;

class ConfigurationManager;
extern ConfigurationManager * g_pConfigManager;

// FRAMESTEP
static const unsigned int FRAMESTEP_INDEX = 0;

// PAUSE
static const unsigned int PAUSE_INDEX = 1;

// PLAYBACK
static const unsigned int PLAYBACK_INDEX = 2;

// SHOWCONFIG
static const unsigned int SHOWCONFIG_INDEX = 3;

// SHOWOSD
static const unsigned int SHOWOSD_INDEX = 4;

// MOVEOSD
static const unsigned int MOVEOSD_INDEX = 5;

// COPYCURSOR
static const unsigned int COPYCURSOR_INDEX = 6;

// COPYPOSITION
static const unsigned int COPYPOSITION_INDEX = 7;

// COPYSPEED
static const unsigned int COPYSPEED_INDEX = 8;

enum UKC : unsigned short
{
	Backspace=8,
	TAB=9,
	UKC_Clear=12,
	Return=13,
	Pause=19,
	UKC_Escape = 27,
	Space=32,
	DoubleQuote = 34,
	Quote = 39,
	Plus = 43,
	Comma = 44,
	Minus=45,
	Period=46,
	Slash=47,
	Num0=48,
	Num1=49,
	Num2=50,
	Num3=51,
	Num4=52,
	Num5=53,
	Num6=54,
	Num7=55,
	Num8=56,
	Num9=57,

	Colon=58,
	SemiColon=59,
	Less=60,
	Equals=61,
	Greater=62,
	Question=63,

	LeftBracket = 91,
	Backslash = 92,
	RightBracket = 93,
	Caret = 94,
	Underscore = 95,
	Backquote = 96,

	A=97,
	B=98,
	C=99,
	D=100,
	E=101,
	F=102,
	G=103,
	H=104,
	I=105,
	J=106,
	K=107,
	L=108,
	M=109,
	N=110,
	O=111,
	P=112,
	Q=113,
	R=114,
	S=115,
	T=116,
	U=117,
	V=118,
	W=119,
	X=120,
	Y=121,
	Z=122,
	
	Delete=127,

	Numpad_0 = 256,
	Numpad_1 =  257,
	Numpad_2 = 258,
	Numpad_3 = 259,
	Numpad_4 = 260,
	Numpad_5 = 261,
	Numpad_6 = 262,
	Numpad_7 = 263,
	Numpad_8 = 264,
	Numpad_9 = 265,
	F1 = 282,
	F2 = 283,
	F3 = 284,
	F4 = 285,
	F5 = 286,
	F6 = 287,
	F7 = 288,
	F8 = 289,
	F9 = 290,
	F10 = 291,
	F11 = 292,
	F12 = 293,
	F13 = 294,
	F14 = 295,
	F15 =296,
	RightShift=303,
	LeftShift=304,
	RightCtrl=305,
	LeftCtrl=306,
	RightAlt=307,
	LeftAlt=308
};

enum EMouseUnityKeycode : unsigned short
{
	LEFTMOUSE=0,
	RIGHTMOUSE=1,
	MIDDLEMOUSE=2
};

typedef struct t_Key
{
public:

	t_Key() {}

	t_Key(unsigned short vkc, unsigned short ukc, const wchar_t * character, void * badFood)
	{

		//this->isShift = false;
		//this->isControl = false;
		//this->isAlt = false;

		this->uUnityKeycode = ukc;
		this->uVirtualKeycode = vkc;
		this->pcszCharacter = character;

	}

	t_Key(unsigned short vkc, unsigned short ukc,const wchar_t * character)
	{


		//this->isMouseKey = MOUSE;
		this->pcszCharacter = character;
		this->uVirtualKeycode = vkc;
		this->uUnityKeycode = ukc;

		//this->isShift = SHIFT;
		//this->isAlt = ALT;
		//this->isControl = CTRL;

	}

	inline void SetKeycodes(unsigned short vkc, unsigned short ukc)
	{
		this->uVirtualKeycode = vkc;
		this->uUnityKeycode = ukc;
	}

	unsigned short uUnityKeycode;

	unsigned short uVirtualKeycode;

	const wchar_t * pcszCharacter;

	//bool isMouseKey;

	//bool isShift;

	//bool isControl;

	//bool isAlt;

	// sigh...
	// ->first = Unity Keycode
	// ->second = Windows Virtual Keycode
protected:
private:
} Key;

// map them by the unity keycode 
// PROBLEM: These states need to be read from a file first.
// DOUBLE PROBLEM: 
static std::map<unsigned short, Key*> keyMap = 
{
{EMouseUnityKeycode::LEFTMOUSE, new Key(VK_LBUTTON, EMouseUnityKeycode::LEFTMOUSE, L"LMouse")},
{EMouseUnityKeycode::RIGHTMOUSE, new Key(VK_RBUTTON, EMouseUnityKeycode::RIGHTMOUSE, L"RMouse")},
{EMouseUnityKeycode::MIDDLEMOUSE, new Key(VK_MBUTTON, EMouseUnityKeycode::MIDDLEMOUSE, L"MMouse")},

{UKC::Backspace, new Key(VK_BACK, UKC::Backspace, L"BkSpc")},
{UKC::TAB, new Key(VK_TAB, UKC::TAB, L"Tab")},
{UKC::UKC_Clear, new Key(VK_CLEAR, UKC::UKC_Clear, L"Clear")},
{UKC::Return, new Key(VK_RETURN, UKC::Return, L"Return")},
{UKC::Pause, new Key(VK_PAUSE, UKC::Pause, L"Pause")},
{UKC::UKC_Escape, new Key(VK_ESCAPE, UKC::UKC_Escape, L"Esc")},
{UKC::Space, new Key(VK_SPACE, UKC::Space, L"Space")},
{UKC::DoubleQuote, new Key(VK_OEM_7, UKC::DoubleQuote, L"\"")},
{UKC::Quote, new Key(VK_OEM_7, UKC::Quote, L"'")},
{UKC::Plus, new Key(VK_OEM_PLUS, UKC::Plus, L"+")},
{UKC::Comma, new Key(VK_OEM_COMMA, UKC::Comma, L",")},
{UKC::Minus, new Key(VK_OEM_MINUS, UKC::Minus, L"-")},
{UKC::Period, new Key(VK_OEM_PERIOD, UKC::Period, L".")},
{UKC::Slash, new Key(VK_OEM_2, UKC::Slash, L"/")},

// 48 - 57 = 0-9
{UKC::Num0, new Key(0x30, UKC::Num0, L"0")},
{UKC::Num1, new Key(0x31, UKC::Num1, L"1")},
{UKC::Num2, new Key(0x32, UKC::Num2, L"2")},
{UKC::Num3, new Key(0x33, UKC::Num3, L"3")},
{UKC::Num4, new Key(0x34, UKC::Num4, L"4")},
{UKC::Num5, new Key(0x35, UKC::Num5, L"5")},
{UKC::Num6, new Key(0x36, UKC::Num6, L"6")},
{UKC::Num7, new Key(0x37, UKC::Num7, L"7")},
{UKC::Num8, new Key(0x38, UKC::Num8, L"8")},
{UKC::Num9, new Key(0x39, UKC::Num9, L"9")},

{UKC::Colon, new Key(VK_OEM_1, UKC::Colon, L":")},
{UKC::SemiColon, new Key(VK_OEM_1, UKC::SemiColon, L";")},
{UKC::Less, new Key(VK_OEM_COMMA, UKC::Less, L"<")},
{UKC::Equals, new Key(VK_OEM_PLUS, UKC::Equals, L"=")},
{UKC::Greater, new Key(VK_OEM_PERIOD, UKC::Greater, L">")},
{UKC::Question, new Key(VK_OEM_2, UKC::Question, L"?")},


{UKC::LeftBracket, new Key(VK_OEM_4,UKC::LeftBracket,L"[")},
{UKC::Backslash, new Key(VK_OEM_5,UKC::Backslash,L"\\")},
{UKC::RightBracket, new Key(VK_OEM_6,UKC::RightBracket,L"]")},
{UKC::Underscore, new Key(VK_OEM_MINUS, UKC::Underscore, L"-")},
{UKC::Backquote, new Key(VK_OEM_3, UKC::Backquote, L"`")},

{UKC::A, new Key(0x41, UKC::A, L"A")},
{UKC::B, new Key(0x42, UKC::B, L"B")},
{UKC::C, new Key(0x43, UKC::C, L"C")},
{UKC::D, new Key(0x44, UKC::D, L"D")},
{UKC::E, new Key(0x45, UKC::E, L"E")},
{UKC::F, new Key(0x46, UKC::F, L"F")},
{UKC::G, new Key(0x47, UKC::G, L"G")},
{UKC::H, new Key(0x48, UKC::H, L"H")},
{UKC::I, new Key(0x49, UKC::I, L"I")},
{UKC::J, new Key(0x4A, UKC::J, L"J")},
{UKC::K, new Key(0x4B, UKC::K, L"K")},
{UKC::L, new Key(0x4C, UKC::L, L"L")},
{UKC::M, new Key(0x4D, UKC::M, L"M")},
{UKC::N, new Key(0x4E, UKC::N, L"N")},
{UKC::O, new Key(0x4F, UKC::O, L"O")},
{UKC::P, new Key(0x50, UKC::P, L"P")},
{UKC::Q, new Key(0x51, UKC::Q, L"Q")},
{UKC::R, new Key(0x52, UKC::R, L"R")},
{UKC::S, new Key(0x53, UKC::S, L"S")},
{UKC::T, new Key(0x54, UKC::T, L"T")},
{UKC::U, new Key(0x55, UKC::U, L"U")},
{UKC::V, new Key(0x56, UKC::V, L"V")},
{UKC::W, new Key(0x57, UKC::W, L"W")},
{UKC::X, new Key(0x58, UKC::X, L"X")},
{UKC::Y, new Key(0x59, UKC::Y, L"Y")},
{UKC::Z, new Key(0x5A, UKC::Z, L"Z")},

{UKC::Delete, new Key(VK_DELETE, UKC::Delete, L"Del")},

{UKC::Numpad_0, new Key(VK_NUMPAD0, UKC::Numpad_0, L"Numpad0")},
{UKC::Numpad_1, new Key(VK_NUMPAD1, UKC::Numpad_1, L"Numpad1")},
{UKC::Numpad_2, new Key(VK_NUMPAD2, UKC::Numpad_2, L"Numpad2")},
{UKC::Numpad_3, new Key(VK_NUMPAD3, UKC::Numpad_3, L"Numpad3")},
{UKC::Numpad_4, new Key(VK_NUMPAD4, UKC::Numpad_4, L"Numpad4")},
{UKC::Numpad_5, new Key(VK_NUMPAD5, UKC::Numpad_5, L"Numpad5")},
{UKC::Numpad_6, new Key(VK_NUMPAD6, UKC::Numpad_6, L"Numpad6")},
{UKC::Numpad_7, new Key(VK_NUMPAD7, UKC::Numpad_7, L"Numpad7")},
{UKC::Numpad_8, new Key(VK_NUMPAD8, UKC::Numpad_8, L"Numpad8")},
{UKC::Numpad_9, new Key(VK_NUMPAD9, UKC::Numpad_9, L"Numpad9")},

{UKC::F1, new Key(VK_F1,UKC::F1,L"F1")},
{UKC::F2, new Key(VK_F2,UKC::F2, L"F2")},
{UKC::F3, new Key(VK_F3,UKC::F3, L"F3")},
{UKC::F4, new Key(VK_F4,UKC::F4, L"F4")},
{UKC::F5, new Key(VK_F5,UKC::F5, L"F5")},
{UKC::F6, new Key(VK_F6,UKC::F6, L"F6")},
{UKC::F7, new Key(VK_F7,UKC::F7, L"F7")},
{UKC::F8, new Key(VK_F8,UKC::F8, L"F8")},
{UKC::F9, new Key(VK_F9,UKC::F9, L"F9")},
{UKC::F10, new Key(VK_F10,UKC::F10, L"F10")},
{UKC::F11, new Key(VK_F11,UKC::F11, L"F11")},
{UKC::F12, new Key(VK_F12,UKC::F12, L"F12")},
{UKC::F13, new Key(VK_F13,UKC::F13, L"F13")},
{UKC::F14, new Key{VK_F14,UKC::F14, L"F14"}},
{UKC::F15, new Key(VK_F15,UKC::F15, L"F15")}
//{UKC::LeftShift, new Key(VK_LSHIFT, UKC::LeftShift, L"LeftShift")},
//{UKC::RightShift, new Key(VK_RSHIFT, UKC::RightShift, L"RightShift")},
//{UKC::LeftAlt, new Key(VK_LMENU, UKC::LeftAlt, L"LeftAlt")},
//{UKC::RightAlt, new Key(VK_RMENU, UKC::RightAlt, L"RightAlt")},
//{UKC::LeftCtrl, new Key(VK_LCONTROL, UKC::LeftCtrl, L"LeftCtrl")},
//{UKC::RightCtrl, new Key(VK_RCONTROL, UKC::RightCtrl, L"RightCtrl")}

};



class ButtonKey
{
public:

	ButtonKey(Key * pKey, const wchar_t * ButtonText, float xPos, float yPos, float width, float height, unsigned int nIndex)
	{

		// decouple these from Key def.. idiot
		this->m_bWasDown = false;
		this->m_bDown = false;
		this->m_bUp = false;
		this->m_nIndex = nIndex;
		this->m_bJustPressed = false;
		this->m_bPressedFromSet = false;
		this->m_bJustSet = false;
		this->m_bTransitiveShift = false;
		this->m_bTransitiveAlt = false;
		this->m_bTransitiveCtrl = false;

		this->m_pTextArea = nullptr;
		this->m_pKey = pKey;
		this->m_pButton = new UnityButton(ButtonText, xPos, yPos, width, height);
	}


	inline void CreateTextArea(float xPos, float yPos, float width, float height)
	{
		this->m_pTextArea = new UnityTextArea(L"Temp", xPos, yPos, width, height, false);
		this->FormatCurrentTextArea();
	}

	inline UnityButton * GetButton()
	{
		return this->m_pButton;
	}
	
	inline Key * GetKey()
	{
		return this->m_pKey;
	}

	inline UnityTextArea * GetTextArea()
	{
		return this->m_pTextArea;
	}
	
	inline void FormatCurrentTextArea()
	{
		std::wstring tempString = L"";
		if (this->m_pKey)
		{
			//if(pNewKey->isAlt)
			if (this->m_bTransitiveShift)
				tempString += L"Shift + ";

			if (this->m_bTransitiveCtrl)
				tempString += L"Ctrl + ";

			if (this->m_bTransitiveAlt)
				tempString += L"Alt + ";

			tempString += this->m_pKey->pcszCharacter;
			this->m_pTextArea->SetAreaText(tempString.c_str());
		}
		else
		{
			this->m_pTextArea->SetAreaText(L"HMMM");
		}
	}

	inline void SafeSetKey(Key * pNewKey,bool actuallyRebound=false)
	{
		if (actuallyRebound)
		{
			this->m_bJustSet = true;
			this->m_bPressedFromSet = true;
			this->m_JustSetTimer = this->m_MaxJustSetTimer;
		}

		this->m_pKey = nullptr;
		this->m_pKey = pNewKey;
		this->FormatCurrentTextArea();
	}

	inline void StripModifiers()
	{
		this->m_bTransitiveAlt = false;
		this->m_bTransitiveCtrl = false;
		this->m_bTransitiveShift = false;
	}

	inline void SetTransitivesFromKeycode(unsigned short uKc)
	{
		switch (uKc)
		{
		case UKC::LeftAlt:
		case UKC::RightAlt:
			this->m_bTransitiveAlt = true;
			break;
		case UKC::LeftCtrl:
		case UKC::RightCtrl:
			this->m_bTransitiveCtrl = true;
			break;
		default:
			break;
		}
	}

	inline bool GetKeyDown(unsigned short key, bool async=true)
	{
		if(async)
			return (GetAsyncKeyState(key) & 0x8000);

		return GetKeyState(key) & 0x8000;
	}

	inline bool GetKeyUp(unsigned short key, bool async=true)
	{
		if(async)
			return (GetAsyncKeyState(key) & 0x01);

		return GetKeyState(key) & 0x01;
	}

	inline bool CheckKeyRaw()
	{
		bool shiftDown = false, ctrlDown = false, altDown = false;
		bool result = false;

		shiftDown = this->GetKeyDown(VK_SHIFT, true);
		ctrlDown = this->GetKeyDown(VK_CONTROL, true);
		altDown = this->GetKeyDown(VK_MENU, true);

		result = (GetAsyncKeyState(this->m_pKey->uVirtualKeycode) & 0x01) ? true : false;
		
		if (!result)
			return false;

		if (this->m_bTransitiveShift) result = shiftDown;
		if (this->m_bTransitiveCtrl) result = ctrlDown;
		if (this->m_bTransitiveAlt) result = altDown;
		return result;
	}
	// Pause, Framestep, CopyCursor, CopyPosition and CopySpeed don't need grace timers
	// because otherwise while paused we couldn't tick their timers, Update isn't running! :)
	inline bool CheckKeyWithoutGrace(bool asyncMain = true)
	{

		bool shiftDown = false, ctrlDown = false, altDown = false;
		bool result = false;

		shiftDown = this->GetKeyDown(VK_SHIFT, true);
		ctrlDown = this->GetKeyDown(VK_CONTROL, true);
		altDown = this->GetKeyDown(VK_MENU, true);

		// This should stay, maybe
		if (this->m_bPressedFromSet)
		{
			this->m_bPressedFromSet = false;
			return false;
		}
		
		// we know these are manual updates, nothing else is calling it otherwise.
		if (GetAsyncKeyState(this->m_pKey->uVirtualKeycode) < 0 && !this->m_bWasDown)
		{
			this->m_bWasDown = true;
			result = false;
			return result;
		}

		if (GetAsyncKeyState(this->m_pKey->uVirtualKeycode) == 0 && this->m_bWasDown)
		{
			this->m_bWasDown = false;
			result = true;

			if (this->m_bTransitiveShift) result = shiftDown;
			if (this->m_bTransitiveCtrl) result = ctrlDown;
			if (this->m_bTransitiveAlt) result = altDown;
			return result;
		}

		// should never get here
		return false;
	}

	inline bool CheckKey(bool asyncMain=true)
	{

		if (this->m_bPressedFromSet)
		{
			this->m_bPressedFromSet = false;
			return false;
		}

		// let grace timer expire this
		if (this->m_bJustPressed)
			return false;

		bool shiftDown = false, ctrlDown = false, altDown = false;
		bool result = false;

		shiftDown = this->GetKeyDown(VK_SHIFT, true);
		ctrlDown = this->GetKeyDown(VK_CONTROL, true);
		altDown = this->GetKeyDown(VK_MENU, true);

		// main keycode down - check modifiers individually
		if (GetKeyDown(this->m_pKey->uVirtualKeycode, asyncMain))
		{
			result = true;

			// Set just pressed and grace timer
			this->m_bJustPressed = true;
			this->m_GracePressedTimer = this->m_MaxGraceTimer;

			// toggle between each
			if (this->m_bTransitiveShift) result = shiftDown;
			if (this->m_bTransitiveCtrl) result = ctrlDown;
			if (this->m_bTransitiveAlt) result = altDown;

		}
		
		return result;
	}


	void UpdateJustSetTimer()
	{
		if (this->m_bJustSet)
		{
			this->m_JustSetTimer -= (1.0f / 60.0f);
			if (this->m_JustSetTimer <= 0.0f)
			{
				this->m_JustSetTimer = 0.0f;
				this->m_bJustSet = false;
				return;
			}
		}
	}

	void UpdateGracePressedTimer()
	{
		if (this->m_bJustPressed)
		{
			this->m_GracePressedTimer -= (1.0f / 60.0f);
			if (this->m_GracePressedTimer <= 0.0f)
			{
				this->m_GracePressedTimer = 0.0f;
				this->m_bJustPressed = false;
				return;
			}
		}
	}

	bool m_bTransitiveShift;
	bool m_bTransitiveAlt;
	bool m_bTransitiveCtrl;

	bool m_bJustSet;
	bool m_bPressedFromSet;

	bool m_bWasDown;
	bool m_bDown;
	bool m_bUp;
	bool m_bJustPressed;

	const float m_MaxJustSetTimer = 0.35f;
	float m_JustSetTimer;

	// 6 frame grace timer
	// ok this is a little silly that these can be "held" toggled, but not Framestep. lol
	const float m_MaxGraceTimer = (6.0f / 60.0f);
	float m_GracePressedTimer;

	unsigned int m_nIndex;
protected:
private:


	Key * m_pKey;
	UnityButton * m_pButton;
	UnityTextArea * m_pTextArea;
};
class ConfigurationManager
{
public:

	ConfigurationManager()
	{
		unsigned short tempKeycode = 0xFFFF;

		this->m_pKeybindParser = new KeybindINIParser();

		this->m_pCurrentDirtyButtonKey = nullptr;
		this->m_bKeybindsMenuActive = true;
		this->m_ppButtonKeys = new ButtonKey *[ConfigurationManager::m_NumButtonKeys];



		// TODO: Fucking make sure the keycode exists in the map, or we're going to crash, lol.
		// I know it's not a lot to ask that the config file not be edited manually, but..
		tempKeycode = this->m_pKeybindParser->GetKeycode(L"Framestep");
		this->m_ppButtonKeys[FRAMESTEP_INDEX] = new ButtonKey(keyMap[tempKeycode], L"Framestep:", g_fDefButtonXPos, g_fDefButtonYPos, g_fDefButtonWidth, g_fDefButtonHeight, FRAMESTEP_INDEX);
		this->m_ppButtonKeys[FRAMESTEP_INDEX]->m_bTransitiveShift = this->m_pKeybindParser->GetIsShift(L"Framestep");
		this->m_ppButtonKeys[FRAMESTEP_INDEX]->m_bTransitiveCtrl = this->m_pKeybindParser->GetIsCtrl(L"Framestep");
		this->m_ppButtonKeys[FRAMESTEP_INDEX]->m_bTransitiveAlt = this->m_pKeybindParser->GetIsAlt(L"Framestep");
		this->m_ppButtonKeys[FRAMESTEP_INDEX]->CreateTextArea(g_fDefTAXPos, g_fDefTAYPos, g_fDefTAWidth, g_fDefTAHeight);

		tempKeycode = this->m_pKeybindParser->GetKeycode(L"Pause");
		this->m_ppButtonKeys[PAUSE_INDEX] = new ButtonKey(keyMap[tempKeycode], L"Pause:", g_fDefButtonXPos, g_fDefButtonYPos + g_fDefButtonHeight, g_fDefButtonWidth, g_fDefButtonHeight, PAUSE_INDEX);
		this->m_ppButtonKeys[PAUSE_INDEX]->m_bTransitiveShift = this->m_pKeybindParser->GetIsShift(L"Pause");
		this->m_ppButtonKeys[PAUSE_INDEX]->m_bTransitiveCtrl = this->m_pKeybindParser->GetIsCtrl(L"Pause");
		this->m_ppButtonKeys[PAUSE_INDEX]->m_bTransitiveAlt = this->m_pKeybindParser->GetIsAlt(L"Pause");
		this->m_ppButtonKeys[PAUSE_INDEX]->CreateTextArea(g_fDefTAXPos, g_fDefTAYPos + g_fDefTAHeight, g_fDefTAWidth, g_fDefTAHeight);

		tempKeycode = this->m_pKeybindParser->GetKeycode(L"Playback");
		this->m_ppButtonKeys[PLAYBACK_INDEX] = new ButtonKey(keyMap[tempKeycode], L"Playback:", g_fDefButtonXPos, g_fDefButtonYPos + g_fDefButtonHeight * 2.0f, g_fDefButtonWidth, g_fDefButtonHeight, PLAYBACK_INDEX);
		this->m_ppButtonKeys[PLAYBACK_INDEX]->m_bTransitiveShift = this->m_pKeybindParser->GetIsShift(L"Playback");
		this->m_ppButtonKeys[PLAYBACK_INDEX]->m_bTransitiveCtrl = this->m_pKeybindParser->GetIsCtrl(L"Playback");
		this->m_ppButtonKeys[PLAYBACK_INDEX]->m_bTransitiveAlt = this->m_pKeybindParser->GetIsAlt(L"Playback");
		this->m_ppButtonKeys[PLAYBACK_INDEX]->CreateTextArea(g_fDefTAXPos, g_fDefTAYPos + g_fDefTAHeight * 2.0f, g_fDefTAWidth, g_fDefTAHeight);

		tempKeycode = this->m_pKeybindParser->GetKeycode(L"ShowConfig");
		this->m_ppButtonKeys[SHOWCONFIG_INDEX] = new ButtonKey(keyMap[tempKeycode], L"ShowConfig:", g_fDefButtonXPos, g_fDefButtonYPos + g_fDefButtonHeight * 3.0f, g_fDefButtonWidth, g_fDefButtonHeight, SHOWCONFIG_INDEX);
		this->m_ppButtonKeys[SHOWCONFIG_INDEX]->m_bTransitiveShift = this->m_pKeybindParser->GetIsShift(L"ShowConfig");
		this->m_ppButtonKeys[SHOWCONFIG_INDEX]->m_bTransitiveCtrl = this->m_pKeybindParser->GetIsCtrl(L"ShowConfig");
		this->m_ppButtonKeys[SHOWCONFIG_INDEX]->m_bTransitiveAlt = this->m_pKeybindParser->GetIsAlt(L"ShowConfig");
		this->m_ppButtonKeys[SHOWCONFIG_INDEX]->CreateTextArea(g_fDefTAXPos, g_fDefTAYPos + g_fDefTAHeight * 3.0f, g_fDefTAWidth, g_fDefTAHeight);

		tempKeycode = this->m_pKeybindParser->GetKeycode(L"ShowOSD");
		this->m_ppButtonKeys[SHOWOSD_INDEX] = new ButtonKey(keyMap[tempKeycode], L"ShowOSD:", g_fDefButtonXPos, g_fDefButtonYPos + g_fDefButtonHeight * 4.0f, g_fDefButtonWidth, g_fDefButtonHeight, SHOWOSD_INDEX);
		this->m_ppButtonKeys[SHOWOSD_INDEX]->m_bTransitiveShift = this->m_pKeybindParser->GetIsShift(L"ShowOSD");
		this->m_ppButtonKeys[SHOWOSD_INDEX]->m_bTransitiveCtrl = this->m_pKeybindParser->GetIsCtrl(L"ShowOSD");
		this->m_ppButtonKeys[SHOWOSD_INDEX]->m_bTransitiveAlt = this->m_pKeybindParser->GetIsAlt(L"ShowOSD");
		this->m_ppButtonKeys[SHOWOSD_INDEX]->CreateTextArea(g_fDefTAXPos, g_fDefTAYPos + g_fDefTAHeight * 4.0f, g_fDefTAWidth, g_fDefTAHeight);

		tempKeycode = this->m_pKeybindParser->GetKeycode(L"MoveOSD");
		this->m_ppButtonKeys[MOVEOSD_INDEX] = new ButtonKey(keyMap[tempKeycode], L"MoveOSD:", g_fDefButtonXPos, g_fDefButtonYPos + g_fDefButtonHeight * 5.0f, g_fDefButtonWidth, g_fDefButtonHeight, MOVEOSD_INDEX);
		this->m_ppButtonKeys[MOVEOSD_INDEX]->m_bTransitiveShift = this->m_pKeybindParser->GetIsShift(L"MoveOSD");
		this->m_ppButtonKeys[MOVEOSD_INDEX]->m_bTransitiveCtrl = this->m_pKeybindParser->GetIsCtrl(L"MoveOSD");
		this->m_ppButtonKeys[MOVEOSD_INDEX]->m_bTransitiveAlt = this->m_pKeybindParser->GetIsAlt(L"MoveOSD");
		this->m_ppButtonKeys[MOVEOSD_INDEX]->CreateTextArea(g_fDefTAXPos, g_fDefTAYPos + g_fDefTAHeight * 5.0f, g_fDefTAWidth, g_fDefTAHeight);

		tempKeycode = this->m_pKeybindParser->GetKeycode(L"CopyCursor");
		this->m_ppButtonKeys[COPYCURSOR_INDEX] = new ButtonKey(keyMap[tempKeycode], L"CopyCursor:", g_fDefButtonXPos, g_fDefButtonYPos + g_fDefButtonHeight * 6.0f, g_fDefButtonWidth, g_fDefButtonHeight, COPYCURSOR_INDEX);
		this->m_ppButtonKeys[COPYCURSOR_INDEX]->m_bTransitiveShift = this->m_pKeybindParser->GetIsShift(L"CopyCursor");
		this->m_ppButtonKeys[COPYCURSOR_INDEX]->m_bTransitiveCtrl = this->m_pKeybindParser->GetIsCtrl(L"CopyCursor");
		this->m_ppButtonKeys[COPYCURSOR_INDEX]->m_bTransitiveAlt = this->m_pKeybindParser->GetIsAlt(L"CopyCursor");
		this->m_ppButtonKeys[COPYCURSOR_INDEX]->CreateTextArea(g_fDefTAXPos, g_fDefTAYPos + g_fDefTAHeight * 6.0f, g_fDefTAWidth, g_fDefTAHeight);

		tempKeycode = this->m_pKeybindParser->GetKeycode(L"CopyPos");
		this->m_ppButtonKeys[COPYPOSITION_INDEX] = new ButtonKey(keyMap[tempKeycode], L"CopyPos:", g_fDefButtonXPos, g_fDefButtonYPos + g_fDefButtonHeight * 7.0f, g_fDefButtonWidth, g_fDefButtonHeight, COPYPOSITION_INDEX);
		this->m_ppButtonKeys[COPYPOSITION_INDEX]->m_bTransitiveShift = this->m_pKeybindParser->GetIsShift(L"CopyPos");
		this->m_ppButtonKeys[COPYPOSITION_INDEX]->m_bTransitiveCtrl = this->m_pKeybindParser->GetIsCtrl(L"CopyPos");
		this->m_ppButtonKeys[COPYPOSITION_INDEX]->m_bTransitiveAlt = this->m_pKeybindParser->GetIsAlt(L"CopyPos");
		this->m_ppButtonKeys[COPYPOSITION_INDEX]->CreateTextArea(g_fDefTAXPos, g_fDefTAYPos + g_fDefTAHeight * 7.0f, g_fDefTAWidth, g_fDefTAHeight);

		tempKeycode = this->m_pKeybindParser->GetKeycode(L"CopySpeed");
		this->m_ppButtonKeys[COPYSPEED_INDEX] = new ButtonKey(keyMap[tempKeycode], L"CopySpeed:", g_fDefButtonXPos, g_fDefButtonYPos + g_fDefButtonHeight * 8.0f, g_fDefButtonWidth, g_fDefButtonHeight, COPYSPEED_INDEX);
		this->m_ppButtonKeys[COPYSPEED_INDEX]->m_bTransitiveShift = this->m_pKeybindParser->GetIsShift(L"CopySpeed");
		this->m_ppButtonKeys[COPYSPEED_INDEX]->m_bTransitiveCtrl = this->m_pKeybindParser->GetIsCtrl(L"CopySpeed");
		this->m_ppButtonKeys[COPYSPEED_INDEX]->m_bTransitiveAlt = this->m_pKeybindParser->GetIsAlt(L"CopySpeed");
		this->m_ppButtonKeys[COPYSPEED_INDEX]->CreateTextArea(g_fDefTAXPos, g_fDefTAYPos + g_fDefTAHeight * 8.0f, g_fDefTAWidth, g_fDefTAHeight);

		this->Framestep = this->m_ppButtonKeys[FRAMESTEP_INDEX];
		this->Pause = this->m_ppButtonKeys[PAUSE_INDEX];
		this->Playback = this->m_ppButtonKeys[PLAYBACK_INDEX];
		this->ToggleConfigActive = this->m_ppButtonKeys[SHOWCONFIG_INDEX];
		this->ToggleOSD = this->m_ppButtonKeys[SHOWOSD_INDEX];
		this->MoveOSD = this->m_ppButtonKeys[MOVEOSD_INDEX];
		this->CopyCursor = this->m_ppButtonKeys[COPYCURSOR_INDEX];
		this->CopyPosition = this->m_ppButtonKeys[COPYPOSITION_INDEX];
		this->CopySpeed = this->m_ppButtonKeys[COPYSPEED_INDEX];

	}


	// kinda useless code
	inline void ResetDefaults()
	{
		this->StripAllModifiersForDefault();

		this->m_ppButtonKeys[FRAMESTEP_INDEX]->SafeSetKey(keyMap[UKC::LeftBracket]);
		this->m_ppButtonKeys[PAUSE_INDEX]->SafeSetKey(keyMap[UKC::F1]);
		this->m_ppButtonKeys[PLAYBACK_INDEX]->SafeSetKey(keyMap[UKC::F4]);
		this->m_ppButtonKeys[SHOWCONFIG_INDEX]->SafeSetKey(keyMap[UKC::F8]);
		this->m_ppButtonKeys[SHOWOSD_INDEX]->SafeSetKey(keyMap[UKC::F9]);
	}

	// kinda useless code
	inline void StripAllModifiersForDefault()
	{
		for (unsigned int i = 0; i < ConfigurationManager::m_NumButtonKeys; i++)
			this->m_ppButtonKeys[i]->StripModifiers();
	}

	inline void DeactivateAll(bool resetActiveDirtyButtonModifiers=false, bool escaped=false)
	{
		for (unsigned int i = 0; i < ConfigurationManager::m_NumButtonKeys; i++)
		{
			//this->m_ppButtonKeys[i]->m_JustSetTimer = 0.0f;
			//this->m_ppButtonKeys[i]->m_bJustPressed = false;
			this->m_ppButtonKeys[i]->GetButton()->Deactivate();
		}

		if (resetActiveDirtyButtonModifiers)
		{
			this->m_pCurrentDirtyButtonKey->StripModifiers();
		}

		if (escaped)
		{
			this->m_pCurrentDirtyButtonKey->FormatCurrentTextArea();
		}

		this->m_pCurrentDirtyButtonKey = nullptr;
	}

	void UpdateButtonKeyTimers()
	{
		for (unsigned int i = 0; i < ConfigurationManager::m_NumButtonKeys; i++)
		{
			this->m_ppButtonKeys[i]->UpdateJustSetTimer();
			this->m_ppButtonKeys[i]->UpdateGracePressedTimer();
		}
	}

	inline void UpdateButtonGUIStates()
	{
		for (unsigned int i = 0; i < ConfigurationManager::m_NumButtonKeys; i++)
		{
			if (this->m_ppButtonKeys[i]->GetButton()->UpdateGUIState())
			{
				if(!this->m_pCurrentDirtyButtonKey)
					this->m_pCurrentDirtyButtonKey = this->m_ppButtonKeys[i];

			}
		}

	}

	inline bool CheckAnnoyingCombinations(unsigned short keyCode)
	{
		//unsigned short toggleConfigKeycode = this->ToggleConfigActive->GetKey()->uUnityKeycode;
		
		for (unsigned int i = 0; i < ConfigurationManager::m_NumButtonKeys; i++)
		{
			// don't check against the thing we're checking
			if (i == SHOWCONFIG_INDEX) continue;
			
			// yes, this is an annoying combination
			if (this->m_ppButtonKeys[i]->GetKey()->uUnityKeycode == keyCode)
				return true;
		}

		return false;
	}

	inline void UpdateTextAreaGUIStates()
	{
		for (unsigned int i = 0; i < ConfigurationManager::m_NumButtonKeys; i++)
		{
			// mmmmmmmmm i don't think so
			//if (!this->m_ppButtonKeys[i]->GetTextArea())
				//continue;

			this->m_ppButtonKeys[i]->GetTextArea()->UpdateGUIState();
		}
	}

	inline void UpdateCurrentDirtyButtonTimer()
	{
		if (!this->m_pCurrentDirtyButtonKey)
			return;

		wchar_t buf[256] = { 0 };
		swprintf(buf, L"Esc or any key - %f", std::ceilf(this->m_pCurrentDirtyButtonKey->GetButton()->GetDirtyTime()));
		this->m_pCurrentDirtyButtonKey->GetTextArea()->SetAreaText(buf);

		// the timer timed out, so we don't need to worry about changing the key, or the modifiers, it falls back.
		if (this->m_pCurrentDirtyButtonKey->GetButton()->UpdateTimer())
		{
			this->m_pCurrentDirtyButtonKey->FormatCurrentTextArea();
			this->DeactivateAll();
		}
	}   

	inline unsigned int GetActiveCount()
	{
		unsigned int count = 0;

		for (unsigned int i = 0; i < ConfigurationManager::m_NumButtonKeys; i++)
		{
			if (this->m_ppButtonKeys[i]->GetButton()->IsActive())
				count++;
		}

		return count;
	}

	inline bool WasAnyJustSet()
	{
		for (unsigned int i = 0; i < ConfigurationManager::m_NumButtonKeys; i++)
		{
			if (this->m_ppButtonKeys[i]->m_bJustSet)
				return true;
		}
		return false;
	}


	inline bool ValidTimeToCheckKey()
	{
		if (this->GetActiveCount() > 0)
			return false;

		if (this->WasAnyJustSet())
			return false;

		return true;
	}

	UnityButton *  GetInitialDirtyButton()
	{
		for (unsigned int i = 0; i < ConfigurationManager::m_NumButtonKeys; i++)
		{
			if (this->m_ppButtonKeys[i]->GetButton()->IsActive())
				return this->m_ppButtonKeys[i]->GetButton();
		}


		return nullptr;
	}

	inline ButtonKey * GetWorkingDirtyButtonKey()
	{
		return this->m_pCurrentDirtyButtonKey;
	}

	inline ButtonKey * GetInitialDirtyButtonKey()
	{
		for (unsigned int i = 0; i < ConfigurationManager::m_NumButtonKeys; i++)
		{
			if (this->m_ppButtonKeys[i]->GetButton()->IsActive())
			{
				return this->m_ppButtonKeys[i];
			}
		}

		return nullptr;
	}

	void UpdateKeybind(ButtonKey*);


	bool m_bKeybindsMenuActive;
	ButtonKey * ToggleOSD;
	ButtonKey * ToggleConfigActive;
	ButtonKey * Pause;
	ButtonKey * Playback;
	ButtonKey * Framestep;
	ButtonKey * MoveOSD;
	ButtonKey * CopyCursor;
	ButtonKey * CopyPosition;
	ButtonKey * CopySpeed;
protected:
private:


	KeybindINIParser * m_pKeybindParser;
	ButtonKey * m_pCurrentDirtyButtonKey;
	ButtonKey ** m_ppButtonKeys;

	static const unsigned int m_NumButtonKeys = 9;
	
};

extern bool IsCtrlModifier(unsigned short);
extern bool IsAltModifier(unsigned short);

extern bool IsAnyModifierKey(unsigned short, bool*, bool*);
//extern Key *
extern Key * Framestep;