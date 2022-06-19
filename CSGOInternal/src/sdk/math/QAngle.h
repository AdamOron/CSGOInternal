#pragma once
#include "Vector.h"
#include <stdio.h>

class QAngle
{
public:
	float m_X, m_Y, m_Z;

	QAngle(float x, float y, float z);
	QAngle();

	float x() const;
	float y() const;
	float z() const;

	void Print() const
	{
		printf("%.3f %.3f %.3f\n", x(), y(), z());
	}

	friend QAngle operator+(const QAngle &a, const QAngle &b)
	{
		return QAngle(
			a.x() + b.x(),
			a.y() + b.y(),
			a.z() + b.z()
		);
	}

	friend QAngle operator-(const QAngle &a, const QAngle &b)
	{
		return QAngle(
			a.x() - b.x(), 
			a.y() - b.y(), 
			a.z() - b.z()
		);
	}

	friend QAngle operator*(const QAngle &a, float b)
	{
		return QAngle(
			a.x() * b,
			a.y() * b,
			a.z() * b
		);
	}

	float LengthSquared()
	{
		return m_X * m_X + m_Y * m_Y + m_Z * m_Z;
	}

	float Length();
};

Vector AnglesToDirection(const QAngle &angles);

QAngle CalcAngle(const Vector &src, const Vector &dst);
