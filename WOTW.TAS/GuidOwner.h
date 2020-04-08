#pragma once

#include "MonoBehaviour.h"
#pragma pack(push, 1)

class GuidOwner : public MonoBehaviour
{
public:

	// 0x0000 - 0x0017 -- MonoBehaviour members.

	// 0x0018 - 0x001F
	unsigned long long MoonGuid_MoonGuid;
protected:
private:
};
#pragma pack(pop)