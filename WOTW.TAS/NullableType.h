#pragma once

#pragma pack(push, 1)

template <typename T>
class NullableType
{
public:

	// 0x0000 
	bool HasValue;

	// 0x0001
	T Value;
protected:
private:
};
#pragma pack(pop)