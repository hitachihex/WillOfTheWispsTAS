#include "stdafx.h"
#include "GUI.h"
#include "EverythingNeedsMe.h"

unsigned long long g_qwGUIInstancePtr = 0x0;
unsigned long long g_qwGUILayoutOptionsDefaultInstance = 0x0;
unsigned long long g_qwGUIContentDefaultInstancePtr = 0x0;
unsigned long long g_qwGUIUtilityInstancePtr = 0x0;
unsigned int g_nOSDFontSize = 32;
float g_fCurrentOSDXPosition = 120.0f;
float g_fCurrentOSDYPosition = 139.0f;


fnGUI_Label GUI_Label = (fnGUI_Label)(0x0);
fnGUILayout_BeginArea GUI_LayoutBeginArea = (fnGUILayout_BeginArea)(0x0);
fnGUILayout_LabelWithOptions GUILayout_LabelWithOptions = (fnGUILayout_LabelWithOptions)(0x0);
fnGUILayout_EndArea GUILayout_EndArea = (fnGUILayout_EndArea)(0x0);
fnGUILabel_ContentAndStyle GUILabel_ContentAndStyle = (fnGUILabel_ContentAndStyle)(0x0);
fnGUI_TextArea GUI_TextArea = (fnGUI_TextArea)(0x0);
fnGUI_Button GUI_Button = (fnGUI_Button)(0x0);

fnInternalDoWindowInjected InternalDoWindowInjected = (fnInternalDoWindowInjected)(0x0);
Rect *g_pPositionForWindow = new Rect(20.0f, 20.0f, 120.0f, 50.0f);
//00007FFFD52D184D | 48:8B0D 2423F303 | mov rcx,qword ptr ds:[7FFFD9203B78] | ; GUILayoutOptions -- default
//.data:00007FFFD9203B78 gameassembly.dll:$43D3B78 #0
String * g_pGUIString = new String();
String * g_pTextAreaString = new String(0x1);
signed long * g_psdwGuiIndexerPtr = nullptr;


GUI * GetGUIInstance()
{
	if (g_qwGUIInstancePtr == 0x0)
		return nullptr;

	unsigned long long rax = *(unsigned long long*)(g_qwGUIInstancePtr);

	rax = *(unsigned long long*)(rax + 0xB8);

	// deref again????
	return (GUI*)(rax);
}

GUILayoutOption * GetDefaultLayoutOptionInstance()
{
	unsigned long long rax = *(unsigned long long*)(g_qwGUILayoutOptionsDefaultInstance);
	rax = *(unsigned long long*)(rax + 0x30);
	rax = *(unsigned long long*)(rax);
	rax = *(unsigned long long*)(rax + 0xB8);

	// maybe don't deref last here?
	rax = *(unsigned long long*)(rax);

	return (GUILayoutOption*)(rax);
}

GUIContent * GetGUIContentDefaultInstance()
{
	g_qwGUIContentDefaultInstancePtr = ((Assembly_BaseAddr) + GAMEASSEMBLY_GUICONTENTDEFAULT_INSTANCE_RVA);
	unsigned long long rax = *(unsigned long long*)(g_qwGUIContentDefaultInstancePtr);

	rax = *(unsigned long long*)(rax + 0xB8);
	rax = *(unsigned long long*)(rax);

	return (GUIContent*)(rax);
}

GUIUtility * GetGUIUtilityInstance()
{
	g_qwGUIUtilityInstancePtr = ((Assembly_BaseAddr) + GAMEASSEMBLY_GUIUTILITYINSTANCE_RVA);
	unsigned long long rax = *(unsigned long long*)(g_qwGUIContentDefaultInstancePtr);
	rax = *(unsigned long long*)(rax + 0xB8);

	return (GUIUtility*)(rax);

}
void CreateLabelledText(Rect * r, String * text)
{
	GUI_Label(r, text);
}

void CreateLabelledTextWithSize(Rect * r, String * text, unsigned int nFontSize)
{

	auto pSkin = GetGUIInstance()->m_pSkin;

	pSkin->m_pLabel->m_pStyleInternal->m_nFontSize = nFontSize;

	GUIContent * pDefaultContent = GetGUIContentDefaultInstance();
	pDefaultContent->m_Text = text;
	pDefaultContent->m_Tooltip = nullptr;

	GUILabel_ContentAndStyle(r, pDefaultContent, pSkin->m_pLabel);
}

void Unity_CreateWindow(Rect* r, String * title, unsigned int id, unsigned long long * fnAddr)
{
	auto guiInst = GetGUIInstance();
	auto pSkin = guiInst->m_pSkin;
	GUIContent * pDefaultContent = GetGUIContentDefaultInstance();

	pDefaultContent->m_Text = title;
	pDefaultContent->m_Tooltip = nullptr;

	r = InternalDoWindowInjected(id, GetGUIUtilityInstance()->s_OriginalID, r, fnAddr, pDefaultContent, pSkin->m_pWindow, pSkin, true);
}

GUIStatics * GetGUIStaticsInstance()
{
	return (GUIStatics*)(*(unsigned long long*)(UnityPlayer_BaseAddr + 0 * 0x08 + 0x14D0D00));
}

bool GUI_HasAnyChanged()
{
	//auto i = *g_psdwGuiIndexerPtr;
	unsigned long long rdx = UnityPlayer_BaseAddr;
	unsigned long long offset = 0x14D0D00;
	unsigned long long rax = *(unsigned long long*)(rdx + 0 * 0x08 + offset);
	if (*(unsigned long*)(rax + 0x54) != 0)
		return true;

	return false;
	//unsigned long ecx = *(unsigned long*)(rdx + *g_psdwGuiIndexerPtr +)
}
