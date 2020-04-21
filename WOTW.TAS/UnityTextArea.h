#pragma once

#include "GUI.h"

// need to bring some poly into this
class UnityTextArea
{
public:

	UnityTextArea(const wchar_t * AreaText, float xPos, float yPos, float width, float height, bool _volatile = false)
	{
		this->m_Text = new String(0x1);
		//String::SetUnknown0(this->m_Text, 1);
		String::Set(this->m_Text, AreaText);
		this->m_Position.Set(xPos, yPos, width, height);
		this->m_bVolatile = _volatile;
	}

	inline void SetAreaText(const wchar_t * NewText)
	{
		if (this->m_Text == nullptr)
			return;

		String::Set(this->m_Text, NewText);
	}

	inline void UpdateGUIState()
	{
		if (this->m_Text == nullptr)
			return;

		if (this->m_bVolatile)
		{
			m_Text = GUI_TextArea(&m_Position, this->m_Text);
		}
		else
		{
			GUI_TextArea(&m_Position, this->m_Text);
		}

	}

	String * m_Text;

	Rect m_Position;

	// this is what we'll use to know to even bother checking GUI.changed
	bool m_bVolatile;
protected:
private:
};