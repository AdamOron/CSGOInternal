#include "Vector.h"
#include <math.h>
#include <stdio.h>

Vector::Vector(float x, float y, float z) :
	m_X(x),
	m_Y(y),
	m_Z(z)
{
}

Vector::Vector(const Vector &vec) :
	Vector(vec.x(), vec.y(), vec.z())
{
}

Vector::Vector() :
	Vector(0, 0, 0)
{
}

float Vector::x() const
{
	return m_X;
}

float Vector::y() const
{
	return m_Y;
}

float Vector::z() const
{
	return m_Z;
}

float Vector::LengthSquared() const
{
	return m_X * m_X + m_Y * m_Y + m_Z * m_Z;
}

float Vector::Length() const
{
	return sqrtf(LengthSquared());
}

float Vector::DistSquared(const Vector &other) const
{
	return powf(m_X - other.m_X, 2) + powf(m_Y - other.m_Y, 2) + powf(m_Z - other.m_Z, 2);
}

float Vector::Dist(const Vector &other) const
{
	return sqrtf(DistSquared(other));
}

bool Vector::Normalize()
{
	float len = Length();

	if (len == 0.f)
		return false;

	m_X /= len;
	m_Y /= len;
	m_Z /= len;

	return true;
}

void Vector::Print() const
{
	printf("%.3f %.3f %.3f\n", m_X, m_Y, m_Z);
}

Vector operator+(const Vector &a, const Vector &b)
{
	return Vector(a.x() + b.x(), a.y() + b.y(), a.z() + b.z());
}

Vector operator-(const Vector &a, const Vector &b)
{
	return Vector(a.x() - b.x(), a.y() - b.y(), a.z() - b.z());
}

Vector operator*(const Vector &vec, float scalar)
{
	return Vector(vec.x() * scalar, vec.y() * scalar, vec.z() * scalar);
}

void Vector::Clear()
{
	m_X = m_Y = m_Z = 0;
}

float DotProduct(const Vector &a, const Vector &b)
{
	return a.x() * b.x() + a.y() * b.y() + a.z() * b.z();
}

bool CompareVectors(const Vector &a, const Vector &b)
{
	return a.x() == b.x() && a.y() == b.y() && a.z() == b.z();
}
