#pragma once

#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include "EasyHookUtils.h"
#include <map>
#include <Xinput.h>
#include <cctype>
#include <cmath>
#include "Core_Input.h"

//
#define M_PI2  3.1415926535897931f

static constexpr unsigned int KINEMATIC_ENABLED = 1;
static constexpr unsigned int KINEMATIC_DISABLED = 0;

enum EInputState
{
	// You did nothing
	DEFAULT_NONE         = 0x0,

	// DPad Left
	LEFT                 = 1 << 0,

	// DPad Right
	RIGHT                = 1 << 1,

	// DPad Up
	UP                   = 1 << 2,

	// DPad Down
	DOWN                 = 1 << 3,

	// A
	JUMP                 = 1 << 4,

	// X
	ABILITY1             = 1 << 5,

	// Y
	ABILITY2             = 1 << 6,

	// B
	ABILITY3             = 1 << 7,

	// LB
	BASH                 = 1 << 8,

	// RB?
	DASH                 = 1 << 9,

	// RIGHT TRIGGER
	GLIDE                = 1 << 10,

	// LEFT TRIGGER
	ABILITY_WHEEL        = 1 << 11,

	// Any Left Joystick Analogue Input
	LEFT_STICK           = 1 << 12,

	// START or PAUSE, etc
	START                = 1 << 13,

	// SELECT or MAP, etc
	SELECT               = 1 << 14,

	GRAPPLE              = 1 << 15,

	UNPAUSE              = 1 << 16,

	SLOWDOWN             = 1 << 17,

	ENABLE_KINEMATICS    = 1 << 18,

	OPENMAP              = 1 << 19,

	OPENINVENTORY        = 1 << 20,

	PAGELEFT             = 1 << 21,

	PAGERIGHT            = 1 << 22

};

typedef struct t_InputRecord
{
public:

	EInputState m_InputState;

	int m_Frames;

	int m_Done;

	unsigned long long m_nLineNo;

	bool Slow;

	float XAxis;

	float YAxis;

	bool Jump;

	bool Grab;

	bool Glide;

	bool Dash;
	
	bool Ability1;
	
	bool Ability2;

	bool Ability3;

	bool HasPos;

	bool HasLoad;

	bool HasKinematicSetting;
	unsigned int Kinematicism;

	bool HasSeed;
	unsigned long m_nSeed;

	bool HasMouse;

	float MousePosX;

	float MousePosY;

	float xPos;
	float yPos;

	std::string ToString()
	{
		std::string result = "";

		result += std::to_string(this->m_Frames);

		if (this->XAxis < 0.0f)
			result += ",Left";

		if (this->XAxis > 0.0f)
			result += ",Right";

		if (this->YAxis > 0.0f)
			result += ",Up";
		
		if (this->YAxis < 0.0f)
			result += ",Down";

		if (this->IsJump())
			result += ",Jump";

		if (this->IsDash())
			result += ",Dash";

		if (this->IsBash())
			result += ",Bash";

		if (this->IsGrab())
			result += ",Grab";

		if (this->IsGlide())
			result += ",Glide";

		if (this->IsAbilityOne())
			result += ",Ability1";

		if (this->IsAbilityTwo())
			result += ",Ability2";

		if (this->IsAbilityThree())
			result += ",Ability3";

		if (this->IsStart())
			result += ",Start";

		if (this->IsUnpause())
			result += ",Unpause";

		if (this->IsSelect())
			result += ",OpenMapInventory";

		if (this->IsMenuLeft())
			result += ",MenuLeft";

		if (this->IsMenuRight())
			result += ",MenuRight";

		if (this->IsOpenInventory())
			result += ",OpenInventory";
		return result;
	}


	/*
	void UpdateState(Core_Input *p)
	{
		g_pAbility1->Update(this->Ability1);
		g_pAbility2->Update(this->Ability2);
		g_pAbility3->Update(this->Ability3);
		g_pJump->Update(this->Jump);
		g_pDash->Update(this->Dash);
	}*/

	void GetRecordState(/*XINPUT_STATE *pState*/)
	{

		/*
		if (!pState) return;

		auto pad = &pState->Gamepad;
		if (this->IsEmpty())
		{
			memset(pad, 0, sizeof(XINPUT_GAMEPAD));
			return;
		}*/


		/*
		// A
		if (this->IsJump())
			pad->wButtons |= XINPUT_GAMEPAD_A;
		
		// X
		if (this->IsAbilityOne())
			pad->wButtons |= XINPUT_GAMEPAD_X;
		
		// Y
		if (this->IsAbilityTwo())
			pad->wButtons |= XINPUT_GAMEPAD_Y;

		// B
		if (this->IsAbilityThree())
			pad->wButtons |= XINPUT_GAMEPAD_B;

		// Back
		if (this->IsSelect())
			pad->wButtons |= XINPUT_GAMEPAD_BACK;
		
		// Left Button \ Shoulder
		if (this->IsBash())
			pad->wButtons |= XINPUT_GAMEPAD_LEFT_SHOULDER;
		
		// Right Button \ Shoulder
		if (this->IsDash())
			pad->wButtons |= XINPUT_GAMEPAD_RIGHT_SHOULDER;

		if (this->IsAbilityWheel())
			pad->bLeftTrigger = 255;

		if (this->IsGlide())
			pad->bRightTrigger = 255;
			*/
		return;
	}

	bool HasFlag(EInputState state, EInputState which)
	{
		return (state & which) == which;
	}

	/*
	bool IsLeft()
	{
		return this->HasFlag(this->m_InputState, EInputState::LEFT);
	}

	bool IsRight()
	{
		return this->HasFlag(this->m_InputState, EInputState::RIGHT);
	}

	bool IsUp()
	{
		return this->HasFlag(this->m_InputState, EInputState::UP);
	}

	bool IsDown()
	{
		return this->HasFlag(this->m_InputState, EInputState::DOWN);
	}*/

	bool IsSlow()
	{
		return this->HasFlag(this->m_InputState, EInputState::SLOWDOWN);
	}

	bool IsJump()
	{
		return this->HasFlag(this->m_InputState, EInputState::JUMP);
	}

	bool IsAbilityOne()
	{
		return this->HasFlag(this->m_InputState, EInputState::ABILITY1);
	}

	bool IsAbilityTwo()
	{
		return this->HasFlag(this->m_InputState, EInputState::ABILITY2);
	}

	bool IsAbilityThree()
	{
		return this->HasFlag(this->m_InputState, EInputState::ABILITY3);
	}

	bool IsBash()
	{
		return this->HasFlag(this->m_InputState, EInputState::BASH);
	}
	
	bool IsGrapple()
	{
		return this->HasFlag(this->m_InputState, EInputState::GRAPPLE);
	}
	bool IsDash()
	{
		return this->HasFlag(this->m_InputState, EInputState::DASH);
	}

	bool IsAbilityWheel()
	{
		return this->HasFlag(this->m_InputState, EInputState::ABILITY_WHEEL);
	}

	bool IsGlide()
	{
		return this->HasFlag(this->m_InputState, EInputState::GLIDE);
	}

	bool IsGrab()
	{
		return this->HasFlag(this->m_InputState, EInputState::GLIDE);
	}

	bool IsLeftStick()
	{
		return this->HasFlag(this->m_InputState, EInputState::LEFT_STICK);
	}

	bool IsStart()
	{
		return this->HasFlag(this->m_InputState, EInputState::START);
	}

	bool IsUnpause()
	{
		return this->HasFlag(this->m_InputState, EInputState::UNPAUSE);
	}

	bool IsSelect()
	{
		return this->HasFlag(this->m_InputState, EInputState::SELECT);
	}

	bool IsOpenInventory()
	{
		return this->HasFlag(this->m_InputState, EInputState::OPENINVENTORY);
	}

	bool IsMenuLeft()
	{
		return this->HasFlag(this->m_InputState, EInputState::PAGELEFT);
	}

	bool IsMenuRight()
	{
		return this->HasFlag(this->m_InputState, EInputState::PAGERIGHT);
	}

	bool IsEmpty()
	{
		return this->m_InputState == EInputState::DEFAULT_NONE;
	}

	
#pragma warning(disable : 4996)

	t_InputRecord(std::string line, unsigned int ln)
	{
		this->m_InputState = EInputState::DEFAULT_NONE;
		this->MousePosX = 0.0f;
		this->MousePosY = 0.0f;
		this->HasMouse = false;
		this->HasLoad = false;
		this->HasSeed = false;
		this->HasKinematicSetting = false;
		this->Kinematicism = KINEMATIC_DISABLED;

		this->xPos = 0.0f;
		this->yPos = 0.0f;
		this->HasPos = false;
		this->XAxis = 0.0f;
		this->YAxis = 0.0f;
		this->Ability1 = false;
		this->Ability2 = false;
		this->Ability3 = false;
		this->Dash = false;
		this->Jump = false;
		this->Glide = false;
		this->Grab = false;
		this->Slow = false;
		

		this->m_nLineNo = ln;
		this->m_Done = 0;

		std::istringstream ss(line);
		std::string token;

		std::vector < std::string> tokens;

		auto delimited = line.find(',');

		while (std::getline(ss, token, ','))
			tokens.push_back(token);

		bool bWasValidToken = false;

		// If we don't even have frames, well, this isn't a valid input record then.
		if (!isdigit(line[0]))
		{
			this->m_Frames = -1;
			return;
		}

		this->m_Frames = (delimited == std::string::npos) ? std::stoul(line) : std::stoul(tokens[0]);
		unsigned int TempState = EInputState::DEFAULT_NONE;

		if (tokens.size() > 1 && delimited != std::string::npos)
		{
			for (unsigned int i = 1; i < tokens.size(); i++)
			{
				token = tokens[i];

				// Just continue again, we already handled cases where we needed to process integers.
				if (isdigit(tokens[i][0]))
					continue;

				auto negativelamb = [](char& ch) { ch = toupper((unsigned char)ch); };
				std::for_each(token.begin(), token.end(), negativelamb);

				auto lhstrim = [](std::string& in)
				{
					//lambception
					auto iter = std::find_if(in.begin(), in.end(), [](char ch) { return !std::isspace((unsigned char)ch); });
					in.erase(in.begin(), iter);
					return in;
				};

				auto rhstrim = [](std::string& in)
				{
					auto iter2 = std::find_if(in.rbegin(), in.rend(), [](char ch) { return !std::isspace((unsigned char)ch); });
					in.erase(iter2.base(), in.end());
					return in;
				};

				// Remove the leading and trailing spaces.
				token = lhstrim(token);
				token = rhstrim(token);

				if (token == "LEFT")
				{
					TempState |= EInputState::LEFT;
					this->XAxis = -1.0f;
					bWasValidToken = true;
					continue;
				}
				else if (token == "SLOW")
				{
					this->Slow = true;
					TempState |= EInputState::SLOWDOWN;
					bWasValidToken = true;
					continue;
				}
				else if (token == "KINEMATIC")
				{
					this->HasKinematicSetting = true;
					this->Kinematicism = std::stoul(tokens[i + 1].c_str(), nullptr);
					bWasValidToken = true;
					continue;
				}
				else if (token == "SEED" || token == "RNG" || token == "RANDOM")
				{
					this->HasSeed = true;
					this->m_nSeed = std::stoul(tokens[i + 1].c_str(), nullptr);
					bWasValidToken = true;
					continue;
				}
				else if (token == "POS" || token == "POSITION")
				{
					this->HasPos = true;
					this->xPos = std::strtof(tokens[i + 1].c_str(), nullptr);
					this->yPos = std::strtof(tokens[i + 2].c_str(), nullptr);
					bWasValidToken = true;
					continue;
				}
				else if (token == "MOUSE")
				{
					this->HasMouse = true;
					this->MousePosX = std::strtof(tokens[i + 1].c_str(), nullptr);
					this->MousePosY = std::strtof(tokens[i + 2].c_str(), nullptr);
					bWasValidToken = true;
					continue;

				}
				else if (token == "LOAD" || token == "RESTORE")
				{
					this->HasLoad = true;
					bWasValidToken = true;
					continue;
				}
				else if (token == "RIGHT")
				{
					TempState |= EInputState::RIGHT;
					this->XAxis = 1.0f;
					bWasValidToken = true;
					continue;
				}
				else if (token == "UP")
				{
					this->YAxis = 1.0f;
					TempState |= EInputState::UP;
					bWasValidToken = true;
					continue;
				}
				else if (token == "DOWN")
				{
					this->YAxis = -1.0f;
					TempState |= EInputState::DOWN;
					bWasValidToken = true;
					continue;
				}
				// im assuming this is attack
				else if (token == "JUMP" || token == "MENUSELECT" || token == "ACTION")
				{
					this->Jump = true;
					TempState |= EInputState::JUMP;
					bWasValidToken = true;
					continue;
				}
				else if (token == "ABILITY1" || token == "BUTTONX")
				{
					this->Ability1 = true;
					TempState |= EInputState::ABILITY1;
					bWasValidToken = true;
					continue;
				}
				else if (token == "ABILITY2" || token == "BUTTONY")
				{
					this->Ability2 = true;
					TempState |= EInputState::ABILITY2;
					bWasValidToken = true;
					continue;
				}
				else if (token == "SELECT" || token == "MAP")
				{
					TempState = EInputState::SELECT;
					bWasValidToken = true;
					continue;
				}

				else if (token == "INV" || token == "INVENTORY")
				{
					TempState |= EInputState::OPENINVENTORY;
					bWasValidToken = true;
					continue;
				}
				else if (token == "MENURIGHT")
				{
					TempState |= EInputState::PAGERIGHT;
					bWasValidToken = true;
					continue;
				}
				else if (token == "MENULEFT")
				{
					TempState |= EInputState::PAGELEFT;
					bWasValidToken = true;
					continue;
				}

				else if (token == "BASH")
				{
					TempState |= EInputState::BASH;
					bWasValidToken = true;
					continue;
				}
				else if (token == "GRAPPLE")
				{
					TempState |= EInputState::GRAPPLE;
					bWasValidToken = true;
				}
				else if (token == "DASH")
				{
					this->Dash = true;
					TempState |= EInputState::DASH;
					bWasValidToken = true;
					continue;
				}
				else if (token == "WHEEL" || token == "ABILITYWHEEL")
				{
					TempState |= EInputState::ABILITY_WHEEL;
					bWasValidToken = true;
					continue;
				}
				else if (token == "GLIDE" || token == "GRAB")
				{
					TempState |= EInputState::GLIDE;
					bWasValidToken = true;
					continue;
				}
	
				else if (token == "START" || token == "PAUSE")
				{
					TempState |= EInputState::START;
					bWasValidToken = true;
					continue;
				}
				else if (token == "UNPAUSE")
				{
					TempState |= EInputState::UNPAUSE;
					bWasValidToken = true;
					continue;
				}
				else if (token == "CANCEL" || token == "ABILITY3" || token == "BUTTONB")
				{
					// this cancels
					this->Ability3 = true;
					TempState |= EInputState::ABILITY3;
					bWasValidToken = true;
					continue;
				}

				else if (token == "ANGLE")
				{
				    float tempFloat = std::strtof(tokens[i + 1].c_str(), nullptr);
					this->XAxis = (float)std::sin(tempFloat * M_PI2 / 180.0f);
					this->YAxis = (float)std::cos(tempFloat * M_PI2 / 180.0f);
					bWasValidToken = true;
					continue;
				}

			}
		}
		this->m_InputState = (EInputState)(TempState);
	}

	t_InputRecord() {}
protected:
private:
}InputRecord;