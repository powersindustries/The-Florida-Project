#include "MeleeAction.h"
#include "Game/Managers/EnemyManager.h"
#include "Game/Managers/GameManager.h"
#include "../Player.h"
#include "Core/Systems/Hash.h"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
MeleeAction::MeleeAction()
{
    m_Direction = g_Player.GetDirection();

    m_BaseRectangle.w = 25;
    m_BaseRectangle.h = 25;

    SetPosition();

    g_Player.DecreaseStamina(m_uiStaminaUseAmount);

    m_SpriteHorizontal = new Sprite(CoreSystems::StringToHash32(std::string("txt_MeleeAttackHorizontal")), g_GameGlobals.ITEM_ANIMATION_SPEED);
    m_SpriteVertical = new Sprite(CoreSystems::StringToHash32(std::string("txt_MeleeAttackVertical")), g_GameGlobals.ITEM_ANIMATION_SPEED);
}


// -------------------------------------------------------
// -------------------------------------------------------
MeleeAction::~MeleeAction()
{
    delete m_SpriteHorizontal;
    delete m_SpriteVertical;
}


// -------------------------------------------------------
// -------------------------------------------------------
void MeleeAction::Update(float* deltaTime)
{
    m_SpriteHorizontal->Update(*deltaTime, m_BaseRectangle);
    m_SpriteVertical->Update(*deltaTime, m_BaseRectangle);

    const uint8_t uiActiveEnemiesSize = static_cast<uint8_t>(g_EnemyManager.m_ActiveEnemies.size());
    for (uint8_t x = 0; x < uiActiveEnemiesSize; ++x)
    {
        EnemyBase* currEnemy = g_EnemyManager.m_ActiveEnemies[x];
        if (currEnemy->m_bActive && CollidedWithEnemy(m_BaseRectangle, currEnemy->m_BaseRectangle))
        {
            currEnemy->KillEnemy();
        }
    }

    if (*deltaTime > (m_fMeleeTimeStamp + m_fMeleeTimer))
    {
        m_bActive = false;
        g_Player.SetHaultMovement(false);
    }
    else
    {
        g_Player.SetHaultMovement(true);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void MeleeAction::Draw(SDL_Renderer* renderer)
{
    switch (m_Direction)
    {
    case Florida::Direction::eUp:
    {
        m_SpriteVertical->Draw(renderer, SDL_FLIP_VERTICAL);
        break;
    }
    case Florida::Direction::eDown:
    {
        m_SpriteVertical->Draw(renderer);
        break;
    }
    case Florida::Direction::eLeft:
    {
        m_SpriteHorizontal->Draw(renderer, SDL_FLIP_HORIZONTAL);
        break;
    }
    case Florida::Direction::eRight:
    {
        m_SpriteHorizontal->Draw(renderer);
        break;
    }
    default:
        break;
    }

    if (g_GameManager.GraphicsDebugModeOn())
    {
        SDL_SetRenderDrawColor(renderer, g_GameGlobals.COLOR_SILVER.r, g_GameGlobals.COLOR_SILVER.g, g_GameGlobals.COLOR_SILVER.b, g_GameGlobals.COLOR_SILVER.a);
        SDL_RenderFillRect(renderer, &m_BaseRectangle);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void MeleeAction::SetPosition()
{
    SDL_Rect& playerRect = g_Player.GetPlayerRectangle();

    switch (m_Direction)
    {
    case Florida::Direction::eUp:
    {
        m_BaseRectangle.x = playerRect.x + ((playerRect.w / 2) - (m_BaseRectangle.w /2));
        m_BaseRectangle.y = playerRect.y - m_BaseRectangle.h - m_iOffset;
        break;
    }
    case Florida::Direction::eDown:
    {
        m_BaseRectangle.x = playerRect.x + ((playerRect.w / 2) - (m_BaseRectangle.w /2));
        m_BaseRectangle.y = playerRect.y + playerRect.h + m_iOffset;
        break;
    }
    case Florida::Direction::eLeft:
    {
        m_BaseRectangle.x = playerRect.x - m_BaseRectangle.w - m_iOffset;
        m_BaseRectangle.y = playerRect.y + ((playerRect.h / 2) - (m_BaseRectangle.h /2));
        break;
    }
    case Florida::Direction::eRight:
    {
        m_BaseRectangle.x = playerRect.x + playerRect.w + m_iOffset;
        m_BaseRectangle.y = playerRect.y + ((playerRect.h / 2) - (m_BaseRectangle.h /2));
        break;
    }
    default:
        break;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void MeleeAction::SetDirection(Direction direction)
{
    m_Direction = direction;

    SetPosition();
}


// -------------------------------------------------------
// -------------------------------------------------------
void MeleeAction::SetInitialTime(float* initialTime)
{
    m_fMeleeTimeStamp = *initialTime;
}

}