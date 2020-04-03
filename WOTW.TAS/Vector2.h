#pragma once

typedef struct t_Vector2
{
public:

	t_Vector2()
	{
		this->m_fX = 0.0f;
		this->m_fY = 0.0f;
	}
	
	t_Vector2(float x, float y)
	{
		this->m_fX = x;
		this->m_fY = y;
	}
	
	// 0x00 - 0x03
	float m_fX;

	// 0x04 - 0x07
	float m_fY;
protected:
private:

} Vector2;