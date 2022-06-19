#pragma once
#include <stdio.h>
#include "Vector.h"

struct matrix3x4_t
{
public:
	inline float Get(int i, int j) const { return m_Values[i][j]; }
	inline void Set(int i, int j, float value) { m_Values[i][j] = value; }

	void Print()
	{
		printf("%.3f %.3f %.3f %.3f\n%.3f %.3f %.3f %.3f\n%.3f %.3f %.3f %.3f\n",
			m_Values[0][0], m_Values[0][1], m_Values[0][2], m_Values[0][3],
			m_Values[1][0], m_Values[1][1], m_Values[1][2], m_Values[1][3],
			m_Values[2][0], m_Values[2][1], m_Values[2][2], m_Values[2][3]);
	}

private:
	float m_Values[3][4];
};

inline Vector GetBonePos(const matrix3x4_t *bones, int boneId)
{
	return Vector(bones[boneId].Get(0, 3), bones[boneId].Get(1, 3), bones[boneId].Get(2, 3));
}
