#pragma once

#include "String.h"
#include "GUILayoutOption.h"
#include "UnityPlayer.h"
//.data:00007FFFD92281C8 gameassembly.dll:$43F81C8 #0 <GUI_sInstance>
#define GAMEASSEMBLY_GUIINSTANCE_RVA 0x43F81C8
#define GAMEASSEMBLY_GUI_LABEL_RVA 0x27EBCC0

//il2cpp:00007FFFD7626F60 gameassembly.dll:$27F6F60 #27F5D60 <GUILayout::BeginArea(Rect screenRect)>
#define GAMEASSEMBLY_GUILAYOUT_BEGINAREA_RVA 0x27F6F60

//il2cpp:00007FFFD7624E10 gameassembly.dll:$27F4E10 #27F3C10 <GUILayout::Label(string text, params GUILayoutOption[] options)>
#define GAMEASSEMBLY_GUILAYOUT_LABEL_WITHOPTIONS_RVA 0x27F4E10

//il2cpp:00007FFFD76275E0 gameassembly.dll : $27F75E0 #27F63E0 <GUILayout::EndArea>
#define GAMEASSEMBLY_GUILAYOUT_ENDAREA_RVA 0x27F75E0


//00007FFFD52D184D | 48:8B0D 2423F303 | mov rcx,qword ptr ds:[7FFFD9203B78] | ; GUILayoutOptions -- default
//.data:00007FFFD9203B78 gameassembly.dll:$43D3B78 #0
#define GAMEASSEMBLY_GUILAYOUTOPTIONSINSTANCE_DEFAULT_RVA 0x43D3B78

//.data:00007FFFD9245100 gameassembly.dll:$4415100 #0
#define GAMEASSEMBLY_GUICONTENTDEFAULT_INSTANCE_RVA 0x4415100

#define GAMEASSEMBLY_GUILABELCONTENTANDSTYLE_RVA 0x27EC0B0

#define GAMEASSEMBLY_GUITEXTAREA_RVA 0x27EE260

//.data:00007FFFD9211980 gameassembly.dll:$43E1980 #0
#define GAMEASSEMBLY_GUIUTILITYINSTANCE_RVA 0x43E1980

//.text:00007FFFECA159F0 unityplayer.dll:$3559F0 #354DF0
#define UNITYPLAYER_INTERNALDOWINDOWINJECTED_RVA 0x3559F0

#pragma pack(push, 1)

typedef struct t_Rect
{
public:

	t_Rect() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->width = 0.0f;
		this->height = 0.0f;
	}

	t_Rect(float nx, float ny, float nw, float nh)
	{
		this->x = nx;
		this->y = ny;
		this->width = nw;
		this->height = nh;
	}

	inline void Set(float nx, float ny, float nw, float nh)
	{
		this->x = nx;
		this->y = ny;
		this->width = nw;
		this->height = nh;
	}

	// 0x00 - 0x03
	float x;

	// 0x04 - 0x07
	float y;

	// 0x08 - 0x0B
	float width;

	// 0x0C - 0x0F
	float height;
protected:
private:
} Rect;

class GUIUtility
{
public:

	// 0x0000 - 0x0003
	int s_SkinMode;

	// 0x0004 - 0x0007
	int s_OriginalID;

	// 0x0008 - 0x000F
	unsigned long long Action_takeCapture;

	// 0x0010 - 0x0017
	unsigned long long Action_releaseCapture;

	// 0x0018 - 0x001F
	unsigned long long FuncIntPtrBool_processEvent;

	// ....
protected:
private:

};
class GUIContent
{
public:


	// 0x0000 - 0x0007
	unsigned long long m_qwUnk0000_0007;

	// 0x0008 - 0x000F
	unsigned long long m_qwUnk0008_000F;

	// 0x0010 - 0x0017
	String * m_Text;

	// 0x0018 - 0x001F
	unsigned long long Texture_m_Image;

	// 0x0020 - 0x0027
	String * m_Tooltip;
protected:
private:
};

class GUIStyle_Internal
{
public:

	// 0x0000 - 0x0133
	unsigned char uc_Unk0000_0133[0x134];

	// 0x0134 - 0x0137
	unsigned int m_nFontSize;
protected:
private:

};
class GUIStyle
{
public:

	// 0x0000 - 0x0007
	unsigned long long m_qwUnk0000_0007;

	// 0x0008 - 0x000F
	unsigned long long m_qwUnk0008_000F;

	// 0x0010 - 0x0017
	GUIStyle_Internal * m_pStyleInternal;
protected:
private:
};

class GUISkin
{
public:

	// 0x0000 - 0x0007
	unsigned long long m_qwUnk0000_0007;

	// 0x0008 - 0x000F
	unsigned long long m_qwUnk0008_000F;

	// 0x0010 - 0x0037
	unsigned char uc_Unk0008_0037[0x38 - 0x10];

	// 0x0038 - 0x003F
	GUIStyle * m_pLabel;

	// 0x0040 - 0x0047
	GUIStyle * m_pTextField;

	// 0x0048 - 0x004F
	GUIStyle * m_pTextArea;

	// 0x0050 - 0x0057
	GUIStyle * m_pWindow;
protected:
private:
};

class GUI
{
public:

	// 0x0000 - 0x0003
	int s_ScrollControlId;

	// 0x0004 - 0x0007
	int s_HotTextField;

	// 0x0008 - 0x000B
	int s_BoxHash;

	// 0x000C - 0x000F
	int s_ButonHash;

	// 0x0010 - 0x0013
	int s_RepeatButtonHash;

	// 0x0014 - 0x0017
	int s_ToggleHash;
	
	// 0x0018 - 0x001B
	int s_ButtonGridHash;

	// 0x001C - 0x001F
	int s_SliderHash;

	// 0x0020 - 0x0023
	int s_BeginGroupHash;

	// 0x0024 - 0x0027
	int s_ScrollviewHash;

	// 0x0028 - 0x002B
	int scrollTroughSide;

	// 0x002C - 0x002F
	unsigned long m_dwUnk002C_002F;

	// 0x0030 - 0x0037
	unsigned long long DateTime_nextScrollStepTime;

	// 0x0038 - 0x003F
	GUISkin * m_pSkin;

	// 0x0040 - 0x0047
	unsigned long long GenericStack_s_ScrollViewStates;


	// --- methods

protected:
private:

};
#pragma pack(pop)

extern unsigned long long g_qwGUIInstancePtr;
extern unsigned long long g_qwGUIContentDefaultInstancePtr;

extern GUI * GetGUIInstance();

extern GUIContent * GetGUIContentDefaultInstance();

typedef void(__fastcall * fnGUI_Label)(Rect*, String*);
extern fnGUI_Label GUI_Label;

typedef void(__fastcall * fnGUILayout_BeginArea)(Rect*);
extern fnGUILayout_BeginArea GUI_LayoutBeginArea;

typedef void(__fastcall * fnGUILayout_LabelWithOptions)(String*, GUILayoutOption*);
extern fnGUILayout_LabelWithOptions GUILayout_LabelWithOptions;

typedef void(__fastcall * fnGUILayout_EndArea)();
extern fnGUILayout_EndArea GUILayout_EndArea;

typedef void(__fastcall * fnGUILabel_ContentAndStyle)(Rect*, GUIContent*, GUIStyle*);
extern fnGUILabel_ContentAndStyle GUILabel_ContentAndStyle;

typedef String*(__fastcall * fnGUI_TextArea)(Rect*, String*);
extern fnGUI_TextArea GUI_TextArea;


typedef Rect*(__fastcall * fnInternalDoWindowInjected)(int, int, Rect*, unsigned long long*, GUIContent*, GUIStyle*, GUISkin*, bool);
extern fnInternalDoWindowInjected InternalDoWindowInjected;
static constexpr wchar_t * GUIStringDefaultText = (wchar_t*)L"This is default text!";

extern unsigned long long g_qwGUILayoutOptionsDefaultInstance;
extern unsigned long long g_qwGUIUtilityInstancePtr;
extern GUILayoutOption * GetDefaultLayoutOptionInstance();
extern GUIUtility * GetGUIUtilityInstance();

extern void CreateLabelledText(Rect*, String*);
extern void CreateLabelledTextWithSize(Rect*, String*, unsigned int);
extern void Unity_CreateWindow(Rect*, String*, unsigned int, unsigned long long*);

extern float g_fCurrentOSDXPosition;
extern float g_fCurrentOSDYPosition;

extern unsigned int g_nOSDFontSize;
extern Rect * g_pPositionForWindow;
extern String * g_pGUIString;
extern String * g_pTextAreaString;