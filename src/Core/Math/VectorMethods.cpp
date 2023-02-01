#include "VectorMethods.h"
#include <math.h>

namespace CoreMath
{


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2f VectorMethods::Add(Vec2f* vector1, Vec2f* vector2)
{
    Vec2f newVector;
    newVector.m_fX = vector1->m_fX + vector2->m_fX;
    newVector.m_fY = vector1->m_fY + vector2->m_fY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3f VectorMethods::Add(Vec3f* vector1, Vec3f* vector2)
{
    Vec3f newVector;
    newVector.m_fX = vector1->m_fX + vector2->m_fX;
    newVector.m_fY = vector1->m_fY + vector2->m_fY;
    newVector.m_fZ = vector1->m_fZ + vector2->m_fZ;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2i VectorMethods::Add(Vec2i* vector1, Vec2i* vector2)
{
    Vec2i newVector;
    newVector.m_iX = vector1->m_iX + vector2->m_iX;
    newVector.m_iY = vector1->m_iY + vector2->m_iY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3i VectorMethods::Add(Vec3i* vector1, Vec3i* vector2)
{
    Vec3i newVector;
    newVector.m_iX = vector1->m_iX + vector2->m_iX;
    newVector.m_iY = vector1->m_iY + vector2->m_iY;
    newVector.m_iZ = vector1->m_iZ + vector2->m_iZ;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2f VectorMethods::Subtract(Vec2f* vector1, Vec2f* vector2)
{
    Vec2f newVector;
    newVector.m_fX = vector1->m_fX - vector2->m_fX;
    newVector.m_fY = vector1->m_fY - vector2->m_fY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3f VectorMethods::Subtract(Vec3f* vector1, Vec3f* vector2)
{
    Vec3f newVector;
    newVector.m_fX = vector1->m_fX - vector2->m_fX;
    newVector.m_fY = vector1->m_fY - vector2->m_fY;
    newVector.m_fZ = vector1->m_fZ - vector2->m_fZ;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2i VectorMethods::Subtract(Vec2i* vector1, Vec2i* vector2)
{
    Vec2i newVector;
    newVector.m_iX = vector1->m_iX - vector2->m_iX;
    newVector.m_iY = vector1->m_iY - vector2->m_iY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3i VectorMethods::Subtract(Vec3i* vector1, Vec3i* vector2)
{
    Vec3i newVector;
    newVector.m_iX = vector1->m_iX - vector2->m_iX;
    newVector.m_iY = vector1->m_iY - vector2->m_iY;
    newVector.m_iZ = vector1->m_iZ - vector2->m_iZ;

    return newVector;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2f VectorMethods::ScalarMultiply(Vec2f* vector, float scalar)
{
    Vec2f newVector;
    newVector.m_fX = scalar * vector->m_fX;
    newVector.m_fY = scalar * vector->m_fY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3f VectorMethods::ScalarMultiply(Vec3f* vector, float scalar)
{
    Vec3f newVector;
    newVector.m_fX = scalar * vector->m_fX;
    newVector.m_fY = scalar * vector->m_fY;
    newVector.m_fZ = scalar * vector->m_fZ;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2i VectorMethods::ScalarMultiply(Vec2i* vector, int scalar)
{
    Vec2i newVector;
    newVector.m_iX = scalar * vector->m_iX;
    newVector.m_iY = scalar * vector->m_iY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3i VectorMethods::ScalarMultiply(Vec3i* vector, int scalar)
{
    Vec3i newVector;
    newVector.m_iX = scalar * vector->m_iX;
    newVector.m_iY = scalar * vector->m_iY;
    newVector.m_iZ = scalar * vector->m_iZ;

    return newVector;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2f VectorMethods::ScalarDivide(Vec2f* vector, float scalar)
{
    Vec2f newVector;
    newVector.m_fX = scalar / vector->m_fX;
    newVector.m_fY = scalar / vector->m_fY;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
Vec3f VectorMethods::ScalarDivide(Vec3f* vector, float scalar)
{
    Vec3f newVector;
    newVector.m_fX = scalar / vector->m_fX;
    newVector.m_fY = scalar / vector->m_fY;
    newVector.m_fZ = scalar / vector->m_fZ;

    return newVector;
}


// ------------------------------------------------------------
// ------------------------------------------------------------
float VectorMethods::VectorLength(Vec2f* vector)
{
    // SquareRoot(x^2 + y^2)
    double vectorLength = sqrt((vector->m_fX * vector->m_fX) + (vector->m_fY * vector->m_fY));
    return static_cast<float>(vectorLength);
}


// ------------------------------------------------------------
// ------------------------------------------------------------
float VectorMethods::VectorLength(Vec3f* vector)
{
    // SquareRoot(x^2 + y^2 + z^2)
    double vectorLength = sqrt((vector->m_fX * vector->m_fX) + (vector->m_fY * vector->m_fY) + (vector->m_fZ * vector->m_fZ));
    return static_cast<float>(vectorLength);
}


float VectorMethods::VectorLength(Vec2i* vector)
{
    // SquareRoot(x^2 + y^2)
    double vectorLength = sqrt((vector->m_iX * vector->m_iX) + (vector->m_iY * vector->m_iY));
    return static_cast<float>(vectorLength);
}

float VectorMethods::VectorLength(Vec3i* vector)
{
    // SquareRoot(x^2 + y^2 + z^2)
    double vectorLength = sqrt((vector->m_iX * vector->m_iX) + (vector->m_iY * vector->m_iY) + (vector->m_iZ * vector->m_iZ));
    return static_cast<float>(vectorLength);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
Vec2f VectorMethods::RotateCounterClockwise(Vec2f* vector, float angleInDegrees)
{
    Vec2f newVector;
    newVector.m_fX = static_cast<float>((vector->m_fX * cos(angleInDegrees)) - (vector->m_fY * sin(angleInDegrees)));
    newVector.m_fY = static_cast<float>((vector->m_fX * sin(angleInDegrees)) + (vector->m_fY * cos(angleInDegrees)));
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
    newVector.m_fX = (1 * vector->m_fX) + (0 * vector->m_fY) + (0 * vector->m_fZ);
    newVector.m_fY = static_cast<float>((0 * vector->m_fX) + (cos(angleInDegrees) * vector->m_fY) + (-1 * sin(angleInDegrees) * vector->m_fZ));
    newVector.m_fZ = static_cast<float>((0 * vector->m_fX) + (sin(angleInDegrees) * vector->m_fY) + (0 * cos(angleInDegrees) * vector->m_fZ));

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
    newVector.m_fX = static_cast<float>((cos(angleInDegrees) * vector->m_fX) + (0 * vector->m_fY) + (sin(angleInDegrees) * vector->m_fZ));
    newVector.m_fY = (0 * vector->m_fX) + (1 * vector->m_fY) + (0 * vector->m_fZ);
    newVector.m_fZ = static_cast<float>((-1 * sin(angleInDegrees) * vector->m_fX) + (cos(angleInDegrees) * vector->m_fY) + (0 * vector->m_fZ));

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
    newVector.m_fX = static_cast<float>((cos(angleInDegrees) * vector->m_fX) + (-1 * sin(angleInDegrees) * vector->m_fY) + (0 * vector->m_fZ));
    newVector.m_fY = static_cast<float>((sin(angleInDegrees) * vector->m_fX) + (cos(angleInDegrees) * vector->m_fY) + (0 * vector->m_fZ));
    newVector.m_fZ = (0 * vector->m_fX) + (0 * vector->m_fY) + (1 * vector->m_fZ);

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
    float dotProduct = (vector1->m_fX * vector2->m_fX) + (vector1->m_fY * vector2->m_fY);
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
    newVector.m_fX = (vector1->m_fY * Vector2f->m_fZ) - (vector1->m_fZ * Vector2f->m_fY);
    newVector.m_fY = (vector1->m_fY * Vector2f->m_fZ) - (vector1->m_fX * Vector2f->m_fZ);
    newVector.m_fZ = (vector1->m_fY * Vector2f->m_fZ) - (vector1->m_fY * Vector2f->m_fX);

    return newVector;
}

}