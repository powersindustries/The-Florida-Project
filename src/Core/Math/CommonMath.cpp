#include "CommonMath.h"
#include <math.h>
#include <float.h>

namespace CoreMath
{


// -------------------------------------------------------
// -------------------------------------------------------
double CommonMath::DistanceBetweenTwoPoints(const int rect1X, const int rect1Y, const int rect2X, const int rect2Y)
{
    return sqrt(pow((rect1X - rect2X), 2) + pow((rect1Y - rect2Y), 2));
}


// -------------------------------------------------------
// -------------------------------------------------------
double CommonMath::DirectionalDistanceBetweenTwoRectangles(const Florida::Direction direction, SDL_Rect& rect1, SDL_Rect& rect2)
{
    switch (direction)
    {
    case Florida::Direction::eUp:
    {
        return abs(rect1.y - (rect2.y + rect2.h));
    }
    case Florida::Direction::eDown:
    {
        return abs((rect1.y + rect1.h) - rect2.y);
    }
    case Florida::Direction::eLeft:
    {
        return abs(rect1.x - (rect2.x + rect2.w));
    }
    case Florida::Direction::eRight:
    {
        return abs((rect1.x + rect1.w) - rect2.x);
    }
    }

    return DBL_MAX;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool CommonMath::CollisionBetweenTwoRectangles(const SDL_Rect& rect1, const SDL_Rect& rect2)
{
    return  rect1.x < rect2.x + rect2.w &&
            rect1.x + rect1.w > rect2.x &&
            rect1.y < rect2.y + rect2.h &&
            rect1.h + rect1.y > rect2.y;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool CommonMath::CollisionBetweenTwoRectanglesWithPadding(const SDL_Rect& rect1, const SDL_Rect& rect2, const int iPadding)
{
    return (rect1.x - iPadding) < rect2.x + rect2.w &&
           (rect1.x + rect1.w + iPadding) > rect2.x &&
           (rect1.y - iPadding) < rect2.y + rect2.h &&
           (rect1.h + rect1.y + iPadding) > rect2.y;
}


// -------------------------------------------------------
// -------------------------------------------------------
double CommonMath::ATan2InDegrees(const int iY, const int iX)
{
    const double dRadians = atan2(iY, iX);
    return dRadians * (180.0 / Florida::g_GameGlobals.PI);
}


// -------------------------------------------------------
// -------------------------------------------------------
double CommonMath::ATan2InRadians(const int iY, const int iX)
{
    return atan2(static_cast<double>(iY), static_cast<double>(iX));
}

}