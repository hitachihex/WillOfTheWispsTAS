#pragma once

#include "EverythingNeedsMe.h"
#define SAVEGAMECONTROLLER_PERFORMLOAD_RVA 0x565080
#pragma pack(push, 1)

class SaveGameController
{
public:

	// 0x0000 - 0x001F
	unsigned char uc_Unk0000_001F[0x1F];



	// --- methods
	inline void PerformLoad()
	{
		((void(__fastcall *)(SaveGameController*))((Assembly_BaseAddr)+SAVEGAMECONTROLLER_PERFORMLOAD_RVA))(this);
	}
protected:
private:
};
#pragma pack(pop)