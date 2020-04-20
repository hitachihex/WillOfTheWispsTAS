#pragma once

#include "GUI.h"
#include "EasyHookUtils.h"

#pragma warning(disable : 4996)
#define _CRT_NON_CONFORMING_SWPRINTFS

enum EUnityButtonState : unsigned int
{
	INACTIVE = 0,
	DIRTY = 1
};

class UnityButton
{
public:

	UnityButton()
	{
		this->m_State = EUnityButtonState::INACTIVE;
		this->m_DirtyTime = 0.0f;
		this->m_Position.Set(0.0f, 0.0f, 0.0f, 0.0f);
		this->m_Text = nullptr;
	}

	UnityButton(const wchar_t * ButtonText, float xPos, float yPos, float width, float height)
	{
		this->m_State = EUnityButtonState::INACTIVE;
		this->m_DirtyTime = 0.0f;
		this->m_Text = new String();
		String::Set(this->m_Text, ButtonText);
		this->m_Position.Set(xPos, yPos, width, height);
	}

	inline float GetDirtyTime()
	{
		return this->m_DirtyTime;
	}

	inline bool IsActive()
	{
		return this->m_State == EUnityButtonState::DIRTY;
	}

	inline void Deactivate()
	{
		this->m_State = EUnityButtonState::INACTIVE;
		this->m_DirtyTime = 0.0f;
	}

	inline void SetButtonTextAsTimer()
	{
		wchar_t buf[128] = { 0 };
		swprintf(buf, L"%f", this->m_DirtyTime);
		String::Set(this->m_Text, buf);
	}

	inline bool UpdateGUIState()
	{
		if (this->m_Text == nullptr)
			return false;

		bool bClicked = GUI_Button(&this->m_Position, m_Text);

		if (bClicked && this->m_State == EUnityButtonState::INACTIVE)
		{
			this->m_State = EUnityButtonState::DIRTY;
			this->m_DirtyTime = this->m_MaxDirtyTime;

			return true;
		}

		return false;
	}

	inline bool UpdateTimer()
	{
		if (this->m_State == EUnityButtonState::DIRTY)
		{
			// 1/60 since we hardcoded this too lol
			this->m_DirtyTime -= (1.0f / 60.0f);
			//this->SetButtonTextAsTimer();
			if (this->m_DirtyTime <= 0.0f)
			{
				this->m_DirtyTime = 0.0f;
				this->m_State = EUnityButtonState::INACTIVE;
				//String::Set(this->m_Text, L"Inactive");
				return true;
			}
		}

		return false;

	}

	EUnityButtonState m_State;

	float m_DirtyTime;

	String * m_Text;

	Rect m_Position;

	const float m_MaxDirtyTime = 5.0f;
protected:
private:
};