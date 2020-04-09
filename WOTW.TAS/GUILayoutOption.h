#pragma once

#pragma pack(push, 1)

enum ELayoutType : unsigned long long
{

	fixedWidth,

	fixedHeight,

	minWidth,

	maxWidth,

	minHeight,

	maxHeight,

	stretchWidth,

	stretchHeight,

	alignStart,

	alignMiddle,

	alignEnd,

	alignJustify,

	equalSize,

	spacing
};

class GUILayoutOption
{
public:

	// 0x0000 - 0x0007
	unsigned long long m_qwUnk0000_0007;

	// 0x0008 - 0x000F
	unsigned long long m_qwUnk0000_000F;

	// 0x0010 - 0x0017
	ELayoutType m_layoutType;

	// 0x0018 - 0x001F
	unsigned long long object_value;
protected:
private:
};
#pragma pack(pop)