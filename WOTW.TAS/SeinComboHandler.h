#pragma once
#include "ArrayWrapper.h"
#include "CharacterState.h"
#include "SeinJumpHandler.h"
#include "EverythingNeedsMe.h"
#include "IComboMove.h"


#define GAMEASSEMBLY_SEINCOMBOHANDLER_ISPERFORMINGATTACKABILITY_RVA 0x616970

//.data:000001EEA3984C20 gameassembly.dll:$43C4C20 #0
#define GAMEASSEMBLY_ICOMBOMOVE_INSTANCE_RVA 0x43C4C20
#pragma pack(push, 1)


// forwarding, don't want inline in cpp
class SeinComboHandler;
typedef bool(__fastcall * fnSeinComboHandler_IsPerformingAttackAbility)(SeinComboHandler*);
extern fnSeinComboHandler_IsPerformingAttackAbility SeinComboHandler_IsPerformingAttackAbility;

class SeinComboHandler : public CharacterState
{
public:

	// 0x0000 - 0x007F - CharacterState members

	// 0x0080 - 0x0177
	unsigned char uc_Unk0080_0177[0x178 - 0x80];

	// 0x0178 - 0x017F
	IComboMove * m_pCurrentComboMove;

	// 0x0180 - 0x0187
	IComboMove * m_pUpcomingComboMove;

	// 0x0188 - 0x018F
	unsigned long long m_qwUnk0188_018F;

	// 0x0190 - 0x0197
	unsigned long long m_qwUnk0190_0197;

	// 0x0198 - 0x019F
	SeinJumpHandler * m_pJumpHandler;

	// methods --

	inline bool IsPerformingAttackAbility()
	{
		return SeinComboHandler_IsPerformingAttackAbility(this);
	}
protected:
private:
};
#pragma pack(pop)
