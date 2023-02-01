#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "GameGlobals.h"

namespace Florida
{

class ActionBase
{
public:
    ActionBase();
    ~ActionBase();

    virtual void Update(float* deltaTime) = 0;
    virtual void Draw(SDL_Renderer* renderer) = 0;

    virtual void SetPosition(int x, int y) = 0;
    virtual void SetDirection(Direction direction) = 0;

    bool CollidedWithEnemy(const SDL_Rect& rect1, const SDL_Rect& rect2);


public:

    SDL_Rect m_BaseRectangle;

    Direction m_Direction;

    bool m_bActive;

};

}
