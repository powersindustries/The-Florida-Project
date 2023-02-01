#pragma once

namespace CoreMath
{


struct Vec2f
{
    float m_fX;
    float m_fY;
};


struct Vec2i
{
    int m_iX;
    int m_iY;
};


struct Vec3f
{
    float m_fX;
    float m_fY;
    float m_fZ;
};


struct Vec3i
{
    int m_iX;
    int m_iY;
    int m_iZ;
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
