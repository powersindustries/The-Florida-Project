#pragma once

namespace Core
{

class Vec2f
{
public:
	Vec2f()
	{
		m_X = 0;
		m_Y = 0;
	}
	Vec2f(const float x, const float y)
	{
		m_X = x;
		m_Y = y;
	}

	float m_X;
	float m_Y;
};

struct Vec2i
{
public:
	Vec2i()
	{
		m_X = 0;
		m_Y = 0;
	}
	Vec2i(const int x, const int y)
	{
		m_X = x;
		m_Y = y;
	}

	int m_X;
	int m_Y;
};

struct Vec3f
{
public:
	Vec3f()
	{
		m_X = 0;
		m_Y = 0;
		m_Z = 0;
	}
	Vec3f(const float x, const float y, const float z)
	{
		m_X = x;
		m_Y = y;
		m_Z = z;
	}

	float m_X;
	float m_Y;
	float m_Z;
};

struct Vec3i
{
public:
	Vec3i()
	{
		m_X = 0;
		m_Y = 0;
		m_Z = 0;
	}
	Vec3i(const int x, const int y, const int z)
	{
		m_X = x;
		m_Y = y;
		m_Z = z;
	}

	int m_X;
	int m_Y;
	int m_Z;
};

class VectorMethods
{
public:

	static Vec2i Add(Vec2i* vector1, Vec2i* vector2);
	static Vec2f Add(Vec2f* vector1, Vec2f* vector2);

	static Vec3i Add(Vec3i* vector1, Vec3i* vector2);
	static Vec3f Add(Vec3f* vector1, Vec3f* vector2);

	static Vec2i Subtract(Vec2i* vector1, Vec2i* vector2);
	static Vec2f Subtract(Vec2f* vector1, Vec2f* vector2);

	static Vec3i Subtract(Vec3i* vector1, Vec3i* vector2);
	static Vec3f Subtract(Vec3f* vector1, Vec3f* vector2);

	static Vec2i ScalarMultiply(Vec2i* vector, int scalar);
	static Vec2f ScalarMultiply(Vec2f* vector, float scalar);

	static Vec3i ScalarMultiply(Vec3i* vector, int scalar);
	static Vec3f ScalarMultiply(Vec3f* vector, float scalar);

	static Vec2f ScalarDivide(Vec2f* vector, float scalar);
	static Vec3f ScalarDivide(Vec3f* vector, float scalar);

	static float VectorLength(Vec2i* vector);
	static float VectorLength(Vec2f* vector);

	static float VectorLength(Vec3i* vector);
	static float VectorLength(Vec3f* vector);

	static Vec2f RotateCounterClockwise(Vec2f* vector, float angleInDegrees);

	static Vec3f RotateAboutX(Vec3f* vector, float angleInDegrees);
	static Vec3f RotateAboutY(Vec3f* vector, float angleInDegrees);
	static Vec3f RotateAboutZ(Vec3f* vector, float angleInDegrees);

	static float AnglesBetweenVector2InDegrees(Vec2f* vector1, Vec2f* vector2);

	static float DotProduct(Vec2f* vector1, Vec2f* vector2);
	static bool ArePerpendicular(Vec2f* vector1, Vec2f* vector2);

	static Vec3f CrossProduct(Vec3f* vector1, Vec3f* vector2);
};

}
