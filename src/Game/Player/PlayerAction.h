#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include <vector>
#include "Actions/ActionBase.h"

namespace Florida
{


enum class ActionType
{
    eNone,
    eBullet,
    eMelee
};


class PlayerAction
{
public:
    PlayerAction();
    ~PlayerAction();

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);

    void InitializeActions();

    void ResetPlayerActions();


private:

    void CreateNewBullet(SDL_Rect& currRect);
    void CreateNewMelee(SDL_Rect& currRect, float deltaTime);

    void UpdateAimIndicator();

    void OnDayNightChangedEvent();


private:

    std::vector<ActionBase*> m_LiveActions;

    SDL_Rect m_AimIndicator;

    const float m_fBulletTimer = 0.5f;
    float m_fBulletTimeStamp = 0.0f;


private:

    friend class Player;
};

}