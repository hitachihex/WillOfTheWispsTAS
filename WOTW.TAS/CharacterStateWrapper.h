#pragma once
#pragma pack(push, 1)

template <class T>
class CharacterStateWrapper
{
public:

	// THIS HAS TO BE AT +0x18, it MUST be. im looking at the code <.<
	// 0x0000 - 0x0017
	unsigned char uc_Unk0000_0017[0x18];

	// 0x18 - 0x1F
	T  State;
protected:
private:
};
#pragma pack(pop)