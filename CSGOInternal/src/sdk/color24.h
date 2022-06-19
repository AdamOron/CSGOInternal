#pragma once

struct color24
{
	short m_R, m_G, m_B;

	void SetR(short r)
	{
		this->m_R = r;
	}

	void SetG(short g)
	{
		this->m_G = g;
	}

	void SetB(short b)
	{				
		this->m_B = b;
	}
};
