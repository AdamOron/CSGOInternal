#pragma once

class Vector
{
public:
	float m_X, m_Y, m_Z;

	Vector(float x, float y, float z);
	Vector(const Vector &vec);
	Vector();

	float x() const;
	float y() const;
	float z() const;

	float LengthSquared() const;
	float Length() const;

	float DistSquared(const Vector &other) const;
	float Dist(const Vector &other) const;

	bool Normalize();

	void Clear();

	friend Vector operator+(const Vector &a, const Vector &b);
	friend Vector operator-(const Vector &a, const Vector &b);
	friend Vector operator*(const Vector &vec, float scalar);

	void Print() const;
};

float DotProduct(const Vector &a, const Vector &b);

using Color = Vector;

bool CompareVectors(const Vector &a, const Vector &b);
