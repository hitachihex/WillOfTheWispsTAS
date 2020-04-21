#pragma once

#include "UnityButton.h"
#include "UnityTextArea.h"
#include <wchar.h>
#include <sstream>

class ButtonWithVolatileField
{
public:

	ButtonWithVolatileField(const wchar_t * buttonText, const wchar_t * textAreaText, float xPos, float yPos, float width, float height) 
	{
		this->m_pButton = new UnityButton(buttonText, xPos, yPos, width, height);
		this->m_pTextArea = new UnityTextArea(textAreaText, xPos + (width + m_TextAreaHorizontalOffset), yPos, m_TextAreaDefaultWidth, m_TextAreaDefaultHeight, true);
	}

	// if this returns true, we know to update whatever setting we've associated with this text field
	bool Update()
	{
		this->m_pTextArea->UpdateGUIState();
		return this->m_pButton->UpdateGUIState2();
	}

	void UpdateTimers()
	{
		this->m_pButton->UpdateTimer();
	}

	bool IsFieldFloat()
	{
		std::wstringstream wss(this->m_pTextArea->m_Text->m_wszBytes);
		float temp;
		wss >> std::noskipws >> temp;
		
		return wss.eof() && !wss.fail();
	}

	bool IsFieldUINT()
	{
		std::wstringstream wss(this->m_pTextArea->m_Text->m_wszBytes);
		unsigned int temp;
		wss >> std::noskipws >> temp;
		return wss.eof() && !wss.fail();
	}

	UnityTextArea * GetTextArea() { return this->m_pTextArea; }
protected:
private:
	UnityButton * m_pButton;
	UnityTextArea * m_pTextArea;

	const float m_TextAreaHorizontalOffset = 2.0f;
	const float m_TextAreaDefaultWidth = 100.0f;
	const float m_TextAreaDefaultHeight = 40.0f;
};