#pragma once

#define ObjectAs(ty) (##ty##*)
#pragma pack(push, 1)


enum EUnityObjectStateFlags : unsigned long
{
	FLAG_NONE =  0x0,

	// if all these flags are enabled then an object
	// is not being activated or deactivated? :think:
	UNKFLAG_00 = 1 << 0,
	UNKFLAG_01 = 1 << 1,
	UNKFLAG_02 = 1 << 2,
	UNKFLAG_03 = 1 << 3,
	// --------------------------------
	OBJECT_PENDING_DESTROY = 1 << 4

};

class ObjectModuleMetadata
{

public:

	// 0x0000 - 0x0007
	unsigned long long m_qwUnk0000_0007;

	// 0x0008 - 0x000F
	unsigned long long m_qwUnk0008_000F;

	// 0x0010 - 0x0017
	char * m_szModuleName;

protected:
private:

};
class ObjectScriptMetadata
{
public:

	// 0x0000 - 0x0007
	ObjectModuleMetadata * m_pModuleMetaData;

	// 0x0008 - 0x000F
	unsigned long long m_qwUnk0000_000F;

	// 0x0010 - 0x0017
	char * m_szScriptName;

protected:
private:
};

// name TBD
class UnityObject
{
public:
	// 0x0000 - 0x0007
	// ##vtable##
	// vtable[0x00]
	virtual void UnkVFunc00() = 0;

	// vtable[0x01]
	virtual void UnkVFunc01() = 0;

	// vtable[0x02]
	virtual void UnkVFunc02() = 0;

	// vtable[0x03]
	virtual void UnkVFunc03() = 0;

	// vtable[0x04]
	virtual void UnkVFunc04() = 0;

	// vtable[0x05]
	virtual void UnkVFunc05() = 0;

	// vtable[0x06]
	virtual void UnkVFunc06() = 0;

	// vtable[0x07]
	virtual void UnkVFunc07() = 0;

	// vtable[0x08]
	virtual void UnkVFunc08() = 0;

	// vtable[0x09]
	virtual void UnkVFunc09() = 0;

	// vtable[0x0A]
	virtual void UnkVFunc0A() = 0;

	// vtable[0x0B]
	virtual void UnkVFunc0B() = 0;

	// vtable[0x0C]
	virtual void UnkVFunc0C() = 0;

	// vtable[0x0D]
	virtual void UnkVFunc0D() = 0;

	// vtable[0x0E]
	virtual void UnkVFunc0E() = 0;

	// vtable[0x0F]
	virtual void UnkVFunc0F() = 0;

	// vtable[0x10]
	virtual void UnkVFunc10() = 0;

	// vtable[0x11]
	virtual void UnkVFunc11() = 0;

	// vtable[0x12]
	virtual void UnkVFunc12() = 0;

	// vtable[0x13]
	virtual void UnkVFunc13() = 0;

	// vtable[0x14]
	virtual void UnkVFunc14() = 0;

	// vtable[0x15]
	virtual void UnkVFunc15() = 0;

	// vtable[0x16]
	virtual void UnkVFunc16() = 0;

	// vtable[0x17]
	virtual void UnkVFunc17() = 0;

	// vtable[0x18]
	virtual void UnkVFunc18() = 0;

	// vtable[0x19]
	virtual void UnkVFunc19() = 0;

	// vtable[0x1A]
	virtual bool IsEnabled() = 0;

	// vtable[0x1B]
	virtual void SetEnabled(bool) = 0;


	// ------------------------------------
	// ------------------------------------

	// 0x0008 - 0x000B
	unsigned long m_dwUnk0008_000B;

	// 0x000C - 0x000F
	unsigned long m_dwFlag000C_000F;

	// 0x0010 - 0x001F
	unsigned char uc_Unk0008_001F[0x20 - 0x10];

	// 0x0020 - 0x0023
	unsigned long m_dwUnk0020_0023;

	// 0x0024 - 0x0027
	unsigned long m_dwUnk0024_0027;

	// 0x0028 - 0x002F
	// Transform?
	unsigned long long m_qwUnk0028_002F;

	// 0x0030 - 0x0037
	// AttachedGameObject
	unsigned long long m_qwUnk0030_0037;

	// Apparently uhh, if an object scale is 0..
	// 0x0038
	bool m_bEnabled;

	// 0x0039
	bool m_bIsActiveAndEnabled;

	// 0x003A - 0x0055
	unsigned char uc_Unk003A_005[0x56 - 0x3A];

	// 0x56
	// Active?
	bool m_bFlag0056;

	// 0x57
	bool m_bFlags0057;

	// 0x0058 - 0x005B;
	EUnityObjectStateFlags m_ObjectStateFlags;

	// 0x005C - 0x008F
	unsigned char uc_Unk005C_008F[0x90 - 0x5C];

	// 0x0090 - 0x0097
	unsigned long long m_qwTransformParent;
protected:
private:

};
class Object
{
public:
	
	// 0x0000 - 0x0007
	ObjectScriptMetadata * m_pMetaData;

	// 0x0008 - 0x000F
	unsigned long long m_qwUnk0000_000F;

	// 0x0010 - 0x0017
	UnityObject * m_pCachedPtr;
protected:
private:
};
#pragma pack(pop)
