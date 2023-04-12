#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>

#include "PlayerMovement.h"
#include "PlayerStatistics.h"
#include "PlayerAction.h"
#include "Core/Types/Sprite.h"

using namespace Core;

namespace Florida
{


struct InteractState
{
    bool m_bHeld = false;
    float m_fTime = 0.0f;
};


class Player
{
public:
    Player();
    ~Player();

    void Initialize();

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);

    SDL_Rect& GetPlayerRectangle() { return m_PlayerRectangle; }
    void SetPlayerRectangle(SDL_Rect rectangle) { m_PlayerRectangle = rectangle; }

    void SetPlayerPosition(int x, int y);
    inline void SetPlayerPositionX(int x) { m_PlayerRectangle.x = x; };
    inline void SetPlayerPositionY(int y) { m_PlayerRectangle.y = y; };

    inline const InteractState& GetInteractState() { return m_InteractState; };

    void TakeDamage(uint8_t uiAmount);
    void Heal(uint8_t uiAmount);
    void DecreaseStamina(uint8_t uiAmount);

    void ShootAmmo();

    void ResetPlayer();


private:

    void InitializePlayerSprite();

    void SwapPrimarySecondaryEquipment();

    void UseStaminaPotion();
    
    void OnDayNightChangedEvent();


public:

    PlayerMovement m_PlayerMovement;
    PlayerAction m_PlayerAction;
    PlayerStatistics m_PlayerStatistics;


private:

    InteractState m_InteractState;

    std::string m_sPlayerFilepath;

    SDL_Rect m_PlayerRectangle;

    Sprite* m_PlayerSprite;

};

extern Player g_Player;
}