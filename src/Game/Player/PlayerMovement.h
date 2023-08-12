#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "GameGlobals.h"

namespace Florida
{

enum class MovementState
{
    eIdle,      // Not moving, but can.
    eMoving,    // Walking, no stamina being used.
    eRunning,   // Running, stamina being used.
    eHault      // No moving or running is allowed.
};

class PlayerMovement
{
public:
    PlayerMovement();
    ~PlayerMovement();

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);

    void SetHaultMovement(bool bHault);

    inline const MovementState& GetMovementState() const { return m_State; };
    inline const Direction& GetDirection() const { return m_Direction; };


private:

    MovementState m_State;

    Direction m_Direction;

    const uint8_t m_uiPlayerSpeed = 2;


private:

    friend class Player;
};

}