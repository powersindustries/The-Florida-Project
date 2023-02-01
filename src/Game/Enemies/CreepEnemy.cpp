#include "CreepEnemy.h"
#include "GameGlobals.h"
#include "../Player/Player.h"
#include "Core/Systems/Logging.h"
#include "Core/Systems/Hash.h"
#include <time.h>
#include "../Managers/MapManager.h"
#include "Core/Math/CommonMath.h"
#include "../Managers/EventManager.h"
#include "../Managers/SoundManager.h"

#define TEXTURE_WIDTH 28
#define TEXTURE_HEIGHT 40

#define BLUE_ID "txt_CreepBlue"
#define GREEN_ID "txt_CreepGreen"
#define YELLOW_ID "txt_CreepYellow"

#define SCRAP_ID "itm_Scrap"
#define WOOD_ID  "itm_Wood"
#define WATER_ID "itm_Water"

#define SCRAP_ANIMATION "txt_ScrapAnimation"
#define WOOD_ANIMATION  "txt_WoodAnimation"
#define WATER_ANIMATION "txt_WaterAnimation"

#define DYING_FX "snd_EnemyDying"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
CreepEnemy::CreepEnemy()
{
    srand(static_cast<unsigned int>(time(NULL)));

    m_BaseRectangle.w = TEXTURE_WIDTH;
    m_BaseRectangle.h = TEXTURE_HEIGHT;

    m_State = CreepState::eMoving;

    m_uiSpeed = static_cast<uint8_t>(rand() % (m_uiMaxSpeed - m_uiMinSpeed + 1) + m_uiMinSpeed);
    if (m_uiSpeed == 1)
    {
        m_Sprite = new Sprite(CoreSystems::StringToHash32(std::string(BLUE_ID)), 90);
    }
    else if (m_uiSpeed == 2)
    {
        m_Sprite = new Sprite(CoreSystems::StringToHash32(std::string(GREEN_ID)), 90);
    }
    else
    {
        m_Sprite = new Sprite(CoreSystems::StringToHash32(std::string(YELLOW_ID)), 90);
    }

    m_DroppableItems.reserve(3);
    m_DroppableItems.push_back(CoreSystems::StringToHash32(std::string(SCRAP_ID)));
    m_DroppableItems.push_back(CoreSystems::StringToHash32(std::string(WOOD_ID)));
    m_DroppableItems.push_back(CoreSystems::StringToHash32(std::string(WATER_ID)));

}


// -------------------------------------------------------
// -------------------------------------------------------
CreepEnemy::~CreepEnemy()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void CreepEnemy::Update(float* deltaTime)
{
    // Update Creep state every 3rd frame. No need to run this logic every frame.
    if (*deltaTime > (m_fUpdateTimeStamp + m_fUpdateTimer))
    {
        m_fUpdateTimeStamp = *deltaTime;

        SDL_Rect& playerRect = g_Player.GetPlayerRectangle();

        switch (m_State)
        {
        case CreepState::eMoving:
        {
            int iEnemyPlayerXOffset = m_BaseRectangle.x - playerRect.x;
            int iEnemyPlayerYOffset = m_BaseRectangle.y - playerRect.y;

            int iEnemyPlayerXOffsetAbs = std::abs(iEnemyPlayerXOffset);
            int iEnemyPlayerYOffsetAbs = std::abs(iEnemyPlayerYOffset);

            if (iEnemyPlayerXOffsetAbs >= iEnemyPlayerYOffsetAbs)
            {
                if (iEnemyPlayerXOffset > 0)
                {
                    m_Direction = Direction::eLeft;
                    m_BaseRectangle.x -= m_uiSpeed;
                }
                else
                {
                    m_Direction = Direction::eRight;
                    m_BaseRectangle.x += m_uiSpeed;
                }
            }
            else
            {
                if (iEnemyPlayerYOffset > 0)
                {
                    m_Direction = Direction::eUp;
                    m_BaseRectangle.y -= m_uiSpeed;
                }
                else
                {
                    m_Direction = Direction::eDown;
                    m_BaseRectangle.y += m_uiSpeed;
                }
            }

            // Check to see if in range to attack.
            const double iDistance = CoreMath::CommonMath::DirectionalDistanceBetweenTwoRectangles(m_Direction, m_BaseRectangle, playerRect);
            if (iDistance <= m_iAttackRange)
            {
                m_State = CreepState::ePreAttack;
                m_fPreAttackTimeStamp = *deltaTime;
            }

            break;
        }
        case CreepState::ePreAttack:
        {
            if (*deltaTime > (m_fPreAttackTimeStamp + m_fPreAttackTimer))
            {
                m_State = CreepState::eAttack;
            }
            break;
        }
        case CreepState::eAttack:
        {
            double iDistance = CoreMath::CommonMath::DirectionalDistanceBetweenTwoRectangles(m_Direction, m_BaseRectangle, playerRect);
            if (iDistance <= m_iDamageRange)
            {
                CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Creep Enemy Attacked!!");
                g_Player.TakeDamage(m_uiDamageAmount);
            }

            m_State = CreepState::ePostAttack;
            m_fPostAttackTimeStamp = *deltaTime;
            break;
        }
        case CreepState::ePostAttack:
        {
            if (*deltaTime > (m_fPostAttackTimeStamp + m_fPostAttackTimer))
            {
                m_State = CreepState::eMoving;
            }
            break;
        }
        default:
        {
            CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Creep enemy state does not exist.");
            break;
        }
        }

    }

    m_Sprite->Update(*deltaTime, m_BaseRectangle);
}


// -------------------------------------------------------
// -------------------------------------------------------
void CreepEnemy::Draw(SDL_Renderer* renderer)
{
    m_Sprite->Draw(renderer, m_Direction == Direction::eRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
}


// -------------------------------------------------------
// -------------------------------------------------------
void CreepEnemy::SetPosition(int x, int y)
{
    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;
}


// -------------------------------------------------------
// -------------------------------------------------------
void CreepEnemy::KillEnemy()
{
    m_bActive = false;

    uint8_t randPercent = rand() % 100;
    if (randPercent > m_uiItemDropRate)
    {
        PickupData* newPickup = new PickupData;
        newPickup->m_Type = InteractionType::ePickup;

        newPickup->m_Rectangle.x = m_BaseRectangle.x;
        newPickup->m_Rectangle.y = m_BaseRectangle.y;
        newPickup->m_Rectangle.w = 25;
        newPickup->m_Rectangle.h = 25;

        newPickup->m_uiPickupTime = 1;
        newPickup->m_uiAmount = 1;

        const uint8_t uiRandomDrop = static_cast<uint8_t>(rand() % m_DroppableItems.size());
        newPickup->m_uiItem = m_DroppableItems[uiRandomDrop];

        if (newPickup->m_uiItem == CoreSystems::StringToHash32(std::string(SCRAP_ID)))
        {
            newPickup->m_Sprite = new Sprite(CoreSystems::StringToHash32(std::string(SCRAP_ANIMATION)), g_GameGlobals.ITEM_ANIMATION_SPEED);
        }
        else if (newPickup->m_uiItem == CoreSystems::StringToHash32(std::string(WOOD_ID)))
        {
            newPickup->m_Sprite = new Sprite(CoreSystems::StringToHash32(std::string(WOOD_ANIMATION)), g_GameGlobals.ITEM_ANIMATION_SPEED);
        }
        else if (newPickup->m_uiItem == CoreSystems::StringToHash32(std::string(WATER_ID)))
        {
            newPickup->m_Sprite = new Sprite(CoreSystems::StringToHash32(std::string(WATER_ANIMATION)), g_GameGlobals.ITEM_ANIMATION_SPEED);
        }

        g_MapManager.m_ActiveMap->m_PickupVector.push_back(newPickup);
    }

    g_SoundManager.PlaySoundByID(DYING_FX);

    g_EventManager.Broadcast(Events::eEnemyDied);

}

}