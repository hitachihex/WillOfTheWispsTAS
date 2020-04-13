#pragma once
#include "AbilityType.h"
#include "ArrayWrapper.h"
#include "CharacterState.h"
#include "SeinJumpHandler.h"
#include "InterfaceDef.h"
#include "EverythingNeedsMe.h"


#define GAMEASSEMBLY_SEINCOMBOHANDLER_ISPERFORMINGATTACKABILITY_RVA 0x616970

//.data:000001EEA3984C20 gameassembly.dll:$43C4C20 #0
#define GAMEASSEMBLY_ICOMBOMOVE_INSTANCE_RVA 0x43C4C20
#pragma pack(push, 1)

static constexpr unsigned int ICOMBOMOVE_GETCOMBOMOVETYPE_VF_INDEX = 0x01;

enum ComboMoveType : unsigned int
{

	Attack,

	MovementAbility,

	AnalogMovement,

	OppositeAnalogMovement,

	ComboMove_Any
};

// forward me
class IComboMove;

class IComboMove
{
public:

	// 0x0000 - 0x0007
	InterfaceDef * m_pInterfaceDef;

	// methods

	inline ComboMoveType get_ComboMoveType()
	{
		bool foundComboMoveRelation = false;
		unsigned short i = 0;
		unsigned long n_Index = 0;
		unsigned long long IComboMoveInstance_Ptr = ((Assembly_BaseAddr)+GAMEASSEMBLY_ICOMBOMOVE_INSTANCE_RVA);
		IComboMoveInstance_Ptr = *(unsigned long long*)(IComboMoveInstance_Ptr);

		ComboMoveType result = ComboMoveType::ComboMove_Any;
		for (i = 0; i < this->m_pInterfaceDef->m_nInheritedByCount; i++)
			if (this->m_pInterfaceDef->m_pInheritanceChain[i].m_Ptr == IComboMoveInstance_Ptr)
			{
				foundComboMoveRelation = true;
				n_Index = this->m_pInterfaceDef->m_pInheritanceChain[i].m_Index;
				break;
			}

		// Fallback instead
		if (!foundComboMoveRelation)
			return ComboMoveType::ComboMove_Any;

		// add rdx, rdx
		i = i + i;

		// lea rax, qword ptr ds:[rbx+0x128]
		unsigned long long rax = (unsigned long long)((unsigned long long)this->m_pInterfaceDef + 0x128);

		// n_Index already set in loop
		// mov ecx, dword ptr ds:[r9+rdx*8+0x08]

		// add ecx, r8d
		n_Index = n_Index + ICOMBOMOVE_GETCOMBOMOVETYPE_VF_INDEX;
		
		// shl rcx, 0x04
		n_Index <<= 0x04;

		// add rax, rcx
		rax = rax + n_Index;

		// mov rdx, qword ptr ds:[rax + 0x08]
		unsigned long long rdx = *(unsigned long long*)(rax + 0x08);

		// mov rcx, rdi
		//unsigned long long rcx = (unsigned long long)(this);

		// jmp qword ptr ds:[rax]
		result = ((ComboMoveType(__fastcall *)(IComboMove*, unsigned long long))*(unsigned long long*)rax)(this, rdx);
		
		return result;
	}

protected:
private:
};


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
