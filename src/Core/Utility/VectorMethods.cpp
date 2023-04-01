#include "VectorMethods.h"
#include <math.h>

namespace Core
{


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2f VectorMethods::Add(Vec2f* vector1, Vec2f* vector2)
{
	Vec2f newVector;
	newVector.m_X = vector1->m_X + vector2->m_X;
	newVector.m_Y = vector1->m_Y + vector2->m_Y;

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3f VectorMethods::Add(Vec3f* vector1, Vec3f* vector2)
{
	Vec3f newVector;
	newVector.m_X = vector1->m_X + vector2->m_X;
	newVector.m_Y = vector1->m_Y + vector2->m_Y;
	newVector.m_Z = vector1->m_Z + vector2->m_Z;

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2i VectorMethods::Add(Vec2i* vector1, Vec2i* vector2)
{
	Vec2i newVector;
	newVector.m_X = vector1->m_X + vector2->m_X;
	newVector.m_Y = vector1->m_Y + vector2->m_Y;

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3i VectorMethods::Add(Vec3i* vector1, Vec3i* vector2)
{
	Vec3i newVector;
	newVector.m_X = vector1->m_X + vector2->m_X;
	newVector.m_Y = vector1->m_Y + vector2->m_Y;
	newVector.m_Z = vector1->m_Z + vector2->m_Z;

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2f VectorMethods::Subtract(Vec2f* vector1, Vec2f* vector2)
{
	Vec2f newVector;
	newVector.m_X = vector1->m_X - vector2->m_X;
	newVector.m_Y = vector1->m_Y - vector2->m_Y;

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3f VectorMethods::Subtract(Vec3f* vector1, Vec3f* vector2)
{
	Vec3f newVector;
	newVector.m_X = vector1->m_X - vector2->m_X;
	newVector.m_Y = vector1->m_Y - vector2->m_Y;
	newVector.m_Z = vector1->m_Z - vector2->m_Z;

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2i VectorMethods::Subtract(Vec2i* vector1, Vec2i* vector2)
{
	Vec2i newVector;
	newVector.m_X = vector1->m_X - vector2->m_X;
	newVector.m_Y = vector1->m_Y - vector2->m_Y;

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3i VectorMethods::Subtract(Vec3i* vector1, Vec3i* vector2)
{
	Vec3i newVector;
	newVector.m_X = vector1->m_X - vector2->m_X;
	newVector.m_Y = vector1->m_Y - vector2->m_Y;
	newVector.m_Z = vector1->m_Z - vector2->m_Z;

	return newVector;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2f VectorMethods::ScalarMultiply(Vec2f* vector, float scalar)
{
	Vec2f newVector;
	newVector.m_X = scalar * vector->m_X;
	newVector.m_Y = scalar * vector->m_Y;

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3f VectorMethods::ScalarMultiply(Vec3f* vector, float scalar)
{
	Vec3f newVector;
	newVector.m_X = scalar * vector->m_X;
	newVector.m_Y = scalar * vector->m_Y;
	newVector.m_Z = scalar * vector->m_Z;

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2i VectorMethods::ScalarMultiply(Vec2i* vector, int scalar)
{
	Vec2i newVector;
	newVector.m_X = scalar * vector->m_X;
	newVector.m_Y = scalar * vector->m_Y;

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3i VectorMethods::ScalarMultiply(Vec3i* vector, int scalar)
{
	Vec3i newVector;
	newVector.m_X = scalar * vector->m_X;
	newVector.m_Y = scalar * vector->m_Y;
	newVector.m_Z = scalar * vector->m_Z;

	return newVector;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2f VectorMethods::ScalarDivide(Vec2f* vector, float scalar)
{
	Vec2f newVector;
	newVector.m_X = scalar / vector->m_X;
	newVector.m_Y = scalar / vector->m_Y;

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3f VectorMethods::ScalarDivide(Vec3f* vector, float scalar)
{
	Vec3f newVector;
	newVector.m_X = scalar / vector->m_X;
	newVector.m_Y = scalar / vector->m_Y;
	newVector.m_Z = scalar / vector->m_Z;

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
float VectorMethods::VectorLength(Vec2f* vector)
{
	// SquareRoot(x^2 + y^2)
	double vectorLength = sqrt((vector->m_X * vector->m_X) + (vector->m_Y * vector->m_Y));
	return static_cast<float>(vectorLength);
}


// ------------------------------------------------------------
// ------------------------------------------------------------
float VectorMethods::VectorLength(Vec3f* vector)
{
	// SquareRoot(x^2 + y^2 + z^2)
	double vectorLength = sqrt((vector->m_X * vector->m_X) + (vector->m_Y * vector->m_Y) + (vector->m_Z * vector->m_Z));
	return static_cast<float>(vectorLength);
}


float VectorMethods::VectorLength(Vec2i* vector)
{
	// SquareRoot(x^2 + y^2)
	double vectorLength = sqrt((vector->m_X * vector->m_X) + (vector->m_Y * vector->m_Y));
	return static_cast<float>(vectorLength);
}

float VectorMethods::VectorLength(Vec3i* vector)
{
	// SquareRoot(x^2 + y^2 + z^2)
	double vectorLength = sqrt((vector->m_X * vector->m_X) + (vector->m_Y * vector->m_Y) + (vector->m_Z * vector->m_Z));
	return static_cast<float>(vectorLength);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2f VectorMethods::RotateCounterClockwise(Vec2f* vector, float angleInDegrees)
{
	Vec2f newVector;
	newVector.m_X = static_cast<float>((vector->m_X * cos(angleInDegrees)) - (vector->m_Y * sin(angleInDegrees)));
	newVector.m_Y = static_cast<float>((vector->m_X * sin(angleInDegrees)) + (vector->m_Y * cos(angleInDegrees)));
	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3f VectorMethods::RotateAboutX(Vec3f* vector, float angleInDegrees)
{
	// Rotation Matrix About X Axis
	// 1 0 0
	// 0 cos(theta) -sin(theta)
	// 0 sin(theta) cos(theta)
	Vec3f newVector;
	newVector.m_X = (1 * vector->m_X) + (0 * vector->m_Y) + (0 * vector->m_Z);
	newVector.m_Y = static_cast<float>((0 * vector->m_X) + (cos(angleInDegrees) * vector->m_Y) + (-1 * sin(angleInDegrees) * vector->m_Z));
	newVector.m_Z = static_cast<float>((0 * vector->m_X) + (sin(angleInDegrees) * vector->m_Y) + (0 * cos(angleInDegrees) * vector->m_Z));

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3f VectorMethods::RotateAboutY(Vec3f* vector, float angleInDegrees)
{
	// Rotation Matrix about Y Axis
	// cos(theta) 0 sin(theta)
	// 0 1 0
	// -sin(theta) cos(theta) 0
	Vec3f newVector;
	newVector.m_X = static_cast<float>((cos(angleInDegrees) * vector->m_X) + (0 * vector->m_Y) + (sin(angleInDegrees) * vector->m_Z));
	newVector.m_Y = (0 * vector->m_X) + (1 * vector->m_Y) + (0 * vector->m_Z);
	newVector.m_Z = static_cast<float>((-1 * sin(angleInDegrees) * vector->m_X) + (cos(angleInDegrees) * vector->m_Y) + (0 * vector->m_Z));

	return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3f VectorMethods::RotateAboutZ(Vec3f* vector, float angleInDegrees)
{
	// Rotation Matrix about Z Axis
	// cos(theta) -sin(theta) 0
	// sin(theta) cos(theta) 0
	// 0 0 1
	Vec3f newVector;
	newVector.m_X = static_cast<float>((cos(angleInDegrees) * vector->m_X) + (-1 * sin(angleInDegrees) * vector->m_Y) + (0 * vector->m_Z));
	newVector.m_Y = static_cast<float>((sin(angleInDegrees) * vector->m_X) + (cos(angleInDegrees) * vector->m_Y) + (0 * vector->m_Z));
	newVector.m_Z = (0 * vector->m_X) + (0 * vector->m_Y) + (1 * vector->m_Z);

	return newVector;
}


float VectorMethods::AnglesBetweenVector2InDegrees(Vec2f* vector1, Vec2f* vector2)
{
	// Angle = Cos-1( dot product(vector1 Vector2f) / ||vector1|| ||Vector2f||
	// Angle = Cos-1(dot product / length)

	float numerator = DotProduct(vector1, vector2);
	float denominator = VectorLength(vector1) * VectorLength(vector2);

	return static_cast<float>(acos(numerator / denominator));
}


// ------------------------------------------------------------
// ------------------------------------------------------------
float VectorMethods::DotProduct(Vec2f* vector1, Vec2f* vector2)
{
	float dotProduct = (vector1->m_X * vector2->m_X) + (vector1->m_Y * vector2->m_Y);
	return dotProduct;
}

bool VectorMethods::ArePerpendicular(Vec2f* vector1, Vec2f* vector2)
{
	return DotProduct(vector1, vector2) == 0;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3f VectorMethods::CrossProduct(Vec3f* vector1, Vec3f* Vector2f)
{
	//          [v1y * v2z - v1z * v2y ]
	// Returns: [v1x * v2x - v1x * v2z ]
	//          [v1z * v2y - v1y * v2x ]
	Vec3f newVector;
	newVector.m_X = (vector1->m_Y * Vector2f->m_Z) - (vector1->m_Z * Vector2f->m_Y);
	newVector.m_Y = (vector1->m_Y * Vector2f->m_Z) - (vector1->m_X * Vector2f->m_Z);
	newVector.m_Z = (vector1->m_Y * Vector2f->m_Z) - (vector1->m_Y * Vector2f->m_X);

	return newVector;
}
}