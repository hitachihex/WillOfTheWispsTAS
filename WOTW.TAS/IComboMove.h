#pragma once

#include "AbilityType.h"
#include "MethodTable.h"
#include "InterfaceDef.h"
#pragma pack(push, 1)

enum ComboMoveType : unsigned int
{

	Attack,

	MovementAbility,

	AnalogMovement,

	OppositeAnalogMovement,

	ComboMove_Any,

	ComboMove_INVALID
};


class IComboMove;

template<typename T>
T VFMethodAddressAs(IComboMove *pInstance, unsigned int index);

template<typename T>
T CallComboMoveVF_As(unsigned long long addr, IComboMove * pInstance, unsigned long long rdx);


class IComboMoveInterface
{
public:

	static constexpr unsigned int GET_COMBOMOVETYPE_INDEX = 0x05;
	static constexpr unsigned int GET_COMBOABILITYTYPE_INDEX = 0x1B;

	// 0x0000 - 0x0017
	IL2CppClass m_Class;

	// 0x0018 - 0x0127
	InterfaceDefinition m_InterfaceDefinition;

	// 0x0128 - 0x0317
	MethodTable funTable[0x1F];
protected:
private:
};

class IComboMove
{
public:

	// 0x0000 - 0x0007
	IComboMoveInterface * m_pInterfaceDef;

	/*
	// methods
	inline unsigned long long GetVFAddressByIndex(unsigned int nVFIndex, unsigned long long *outRdx)
	{
		bool foundComboMoveRelation = false;
		unsigned long long vfAddress = 0x0;
		unsigned int i = 0, n_Index = 0;
		unsigned long long IComboMoveInstance_Ptr = *(unsigned long long*)((Assembly_BaseAddr)+GAMEASSEMBLY_ICOMBOMOVE_INSTANCE_RVA);

		for (i = 0; i < this->m_pInterfaceDef->m_nInheritedByCount; i++)
		{
			if (this->m_pInterfaceDef->m_pInheritanceChain[i].m_Ptr == IComboMoveInstance_Ptr)
			{
				foundComboMoveRelation = true;
				n_Index = this->m_pInterfaceDef->m_pInheritanceChain[i].m_Index;
				break;
			}
		}

		if (!foundComboMoveRelation)
			return vfAddress;

		// add rdx, rdx
		//i = i + i;

		// lea rax, qword ptr ds:[rbx+0x128]
		vfAddress = (unsigned long long)((unsigned long long)this->m_pInterfaceDef + 0x128);

		// n_Index already set in loop
		// mov ecx, dword ptr ds:[r9+rdx*8+0x08]

		// add ecx, r8d
		n_Index = n_Index + nVFIndex;

		// shl rcx, 0x04
		n_Index <<= 0x04;

		// add rax, rcx
		vfAddress = vfAddress + n_Index;

		// mov rdx, qword ptr ds:[rax + 0x08]
		*outRdx = *(unsigned long long*)(vfAddress + 0x08);

		// mov rcx, rdi
		//unsigned long long rcx = (unsigned long long)(this);

		// jmp qword ptr ds:[rax]
		return (*(unsigned long long*)(vfAddress));
	}

	inline ComboMoveType get_ComboMoveType()
	{
		ComboMoveType result = ComboMoveType::ComboMove_INVALID;

		unsigned long long rdx = 0;
		unsigned long long vfAddr = this->GetVFAddressByIndex(ICOMBOMOVE_GETCOMBOMOVETYPE_VF_INDEX, &rdx);

		if (!vfAddr) return result;

		result = CallComboMoveVF_As<ComboMoveType>(vfAddr, this, rdx);
		return result;
	}

	// so for abilityType, we pass in 0x17? ((0x17+0x4) << 4) = 0x1B0
	// ability type get to is? 1b0 from 128?
	inline AbilityType get_ComboAbilityType()
	{
		AbilityType result = AbilityType::NoneAbility;
		unsigned long long rdx = 0;
		unsigned long long vfAddr = this->GetVFAddressByIndex(ICOMBOMOVE_GETCOMBOABILITYTYPE_VF_INDEX, &rdx);

		if (!vfAddr) return result;

		result = CallComboMoveVF_As<AbilityType>(vfAddr, this, rdx);
		return result;
	}*/

	inline ComboMoveType get_ComboMoveType()
	{
		return this->m_pInterfaceDef->funTable[IComboMoveInterface::GET_COMBOMOVETYPE_INDEX].As<ComboMoveType>(this);
	}

	inline AbilityType get_ComboAbilityType()
	{
		return this->m_pInterfaceDef->funTable[IComboMoveInterface::GET_COMBOABILITYTYPE_INDEX].As<AbilityType>(this);
	}

protected:
private:
};

#pragma pack(pop)

template<typename T>
T VFMethodAddressAs(IComboMove *pInstance, unsigned int index)
{
	unsigned long long methodAddr = pInstance->m_pInterfaceDef->funTable[index].MethodAddress;
	IL2CppMethod * pArg = pInstance->m_pInterfaceDef->funTable[index].pMethodArgument;

	return ((T(__fastcall *)(IComboMove*, IL2CppMethod*))methodAddr)(pInstance, pArg);
}

template<typename T>
T CallComboMoveVF_As(unsigned long long addr, IComboMove * pInstance, unsigned long long rdx)
{
	return ((T(__fastcall *)(IComboMove*, unsigned long long))addr)(pInstance, rdx);
}