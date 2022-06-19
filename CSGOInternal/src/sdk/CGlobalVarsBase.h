#pragma once
#include <cstdint>

class CGlobalVarsBase
{
private:
	uint8_t _pad0[16];
public:
	float m_fCurTime;
private:
	uint8_t _pad1[8];
public:
	int m_iTickCount;
	float m_fTickInterval;
};
