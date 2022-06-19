#include "QAngle.h"
#include "mathf.h"

QAngle::QAngle(float x, float y, float z) :
	m_X(x),
	m_Y(y),
	m_Z(z)
{
}

QAngle::QAngle() :
	QAngle(0, 0, 0)
{
}

float QAngle::x() const
{
	return m_X;
}

float QAngle::y() const
{
	return m_Y;
}

float QAngle::z() const
{
	return m_Z;
}

float QAngle::Length()
{
	return sqrtf(LengthSquared());
}

QAngle CalcAngle(const Vector &src, const Vector &dst)
{
	Vector forward = dst - src;

	return QAngle(
		RadToDeg(acosf(forward.z() / forward.Length())) - 90.f,
		RadToDeg(atan2f(forward.y(), forward.x())),
		0.f
	);
}

Vector AnglesToDirection(const QAngle &angles)
{
	return Vector(
		cosf(DegToRad(angles.m_X)) * cosf(DegToRad(angles.m_Y)),
		cosf(DegToRad(angles.m_X)) * sinf(DegToRad(angles.m_Y)),
		-sinf(DegToRad(angles.m_X))
	);
}
