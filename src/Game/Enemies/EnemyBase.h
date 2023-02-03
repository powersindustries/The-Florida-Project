#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include "Core/Types/Sprite.h"
#include "GameGlobals.h"


namespace Florida
{

enum class EnemyTypes
{
    eCreep
};


class EnemyBase
{
public:
    EnemyBase();
    ~EnemyBase();

    virtual void Update(float deltaTime) = 0;
    virtual void Draw(SDL_Renderer* renderer) = 0;

    virtual void SetPosition(int x, int y) = 0;
    
    virtual void KillEnemy() = 0;

public:

    Direction m_Direction;

    SDL_Rect m_BaseRectangle;

    CoreTypes::Sprite* m_Sprite;

    bool m_bActive;

};

}
