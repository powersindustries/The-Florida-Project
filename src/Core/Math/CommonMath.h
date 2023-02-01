#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include "GameGlobals.h"

namespace CoreMath
{


class CommonMath
{
public:

    static double DistanceBetweenTwoPoints(const int rect1X, const int rect1Y, const int rect2X, const int rect2Y);
    static double DirectionalDistanceBetweenTwoRectangles(const Florida::Direction direction, SDL_Rect& rect1, SDL_Rect& rect2);
    
    static bool CollisionBetweenTwoRectangles(const SDL_Rect& rect1, const SDL_Rect& rect2);
    static bool CollisionBetweenTwoRectanglesWithPadding(const SDL_Rect& rect1, const SDL_Rect& rect2, const int iPadding);


    static double ATan2InDegrees(const int iY, const int iX);
    static double ATan2InRadians(const int iY, const int iX);

};
}
