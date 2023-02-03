#include "BulletAction.h"
#include "Game/Managers/EnemyManager.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/Systems/Hash.h"

#define ARROW_VERTICAL_ID "txt_ArrowVertical"
#define ARROW_HORIZONTAL_ID "txt_ArrowHorizontal"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
BulletAction::BulletAction()
    : m_SpriteVertical(nullptr)
{
    m_BaseRectangle.w = 25;
    m_BaseRectangle.h = 25;

    m_SpriteVertical   = new CoreTypes::Sprite(CoreSystems::StringToHash32(std::string(ARROW_VERTICAL_ID)), CoreTypes::SpriteType::eNonAnimated);
    m_SpriteHorizontal = new CoreTypes::Sprite(CoreSystems::StringToHash32(std::string(ARROW_HORIZONTAL_ID)), CoreTypes::SpriteType::eNonAnimated);
}


// -------------------------------------------------------
// -------------------------------------------------------
BulletAction::~BulletAction()
{
    delete m_SpriteHorizontal;
    delete m_SpriteVertical;
}


// -------------------------------------------------------
// -------------------------------------------------------
void BulletAction::Update(float deltaTime)
{
    const uint8_t uiActiveEnemiesSize = static_cast<uint8_t>(g_EnemyManager.m_ActiveEnemies.size());
    for (uint8_t x = 0; x < uiActiveEnemiesSize; ++x)
    {
        EnemyBase* currEnemy = g_EnemyManager.m_ActiveEnemies[x];
        if (currEnemy->m_bActive && CollidedWithEnemy(m_BaseRectangle, currEnemy->m_BaseRectangle))
        {
            m_bActive = false;

            currEnemy->KillEnemy();
            break;
        }
    }

    UpdateBulletPosition();

    if (m_Direction == Direction::eUp || m_Direction == Direction::eDown)
    {
        m_SpriteVertical->Update(deltaTime, m_BaseRectangle);
    }
    else
    {
        m_SpriteHorizontal->Update(deltaTime, m_BaseRectangle);
    }

    // Remove bullet if out of screen bounds.
    if (m_BaseRectangle.x < 0 || m_BaseRectangle.x > CoreManagers::g_SettingsManager.GetScreenWidth())
    {
        m_bActive = false;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void BulletAction::Draw(SDL_Renderer* renderer)
{
    switch (m_Direction)
    {
    case Direction::eRight:
    {
        m_SpriteHorizontal->Draw(renderer);
        break;
    }
    case Direction::eLeft:
    {
        m_SpriteHorizontal->Draw(renderer, SDL_FLIP_HORIZONTAL);
        break;
    }
    case Direction::eUp:
    {
        m_SpriteVertical->Draw(renderer);
        break;
    }
    case Direction::eDown:
    {
        m_SpriteVertical->Draw(renderer, SDL_FLIP_VERTICAL);
        break;
    }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void BulletAction::SetPosition(int x, int y)
{
    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;
}



// -------------------------------------------------------
// -------------------------------------------------------
void BulletAction::SetDirection(Direction direction)
{
    m_Direction = direction;
}


// -------------------------------------------------------
// -------------------------------------------------------
void BulletAction::UpdateBulletPosition()
{
    switch (m_Direction)
    {
    case Direction::eRight:
    {
        m_BaseRectangle.x += m_uiSpeed;
        break;
    }
    case Direction::eLeft:
    {
        m_BaseRectangle.x -= m_uiSpeed;
        break;
    }
    case Direction::eUp:
    {
        m_BaseRectangle.y -= m_uiSpeed;
        break;
    }
    case Direction::eDown:
    {
        m_BaseRectangle.y += m_uiSpeed;
        break;
    }
    }
}

}