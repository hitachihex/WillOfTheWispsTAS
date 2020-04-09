#include "stdafx.h"
#include "GUI.h"
#include "EverythingNeedsMe.h"

unsigned long long g_qwGUIInstancePtr = 0x0;
unsigned long long g_qwGUILayoutOptionsDefaultInstance = 0x0;
unsigned long long g_qwGUIContentDefaultInstancePtr = 0x0;

fnGUI_Label GUI_Label = (fnGUI_Label)(0x0);
fnGUILayout_BeginArea GUI_LayoutBeginArea = (fnGUILayout_BeginArea)(0x0);
fnGUILayout_LabelWithOptions GUILayout_LabelWithOptions = (fnGUILayout_LabelWithOptions)(0x0);
fnGUILayout_EndArea GUILayout_EndArea = (fnGUILayout_EndArea)(0x0);
fnGUILabel_ContentAndStyle GUILabel_ContentAndStyle = (fnGUILabel_ContentAndStyle)(0x0);

//00007FFFD52D184D | 48:8B0D 2423F303 | mov rcx,qword ptr ds:[7FFFD9203B78] | ; GUILayoutOptions -- default
//.data:00007FFFD9203B78 gameassembly.dll:$43D3B78 #0
String * g_pGUIString = new String();

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

