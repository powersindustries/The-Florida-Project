#include "PlayerAction.h"
#include "Player.h"
#include "Actions/BulletAction.h"
#include "Actions/MeleeAction.h"
#include "../Managers/ItemManager.h"
#include "../Managers/EventManager.h"
#include "../Managers/SoundManager.h"
#include "../Managers/GameManager.h"
#include "Core/Managers/InputManager.h"
#include "Core/Systems/Hash.h"

#define HAMMER_SOUND_ID "snd_HammerSwing"
#define ARROW_SOUND_ID "snd_ArrowShot"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
PlayerAction::PlayerAction()
{
    m_AimIndicator.x = 0;
    m_AimIndicator.y = 0;
    m_AimIndicator.w = 3;
    m_AimIndicator.h = 3;
}


// -------------------------------------------------------
// -------------------------------------------------------
PlayerAction::~PlayerAction()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerAction::Update(float deltaTime)
{
    UpdateAimIndicator();

    // Update active actions.
    const uint8_t uiLiveActionSize = static_cast<uint8_t>(m_LiveActions.size());
    for (uint8_t x = 0; x < uiLiveActionSize; ++x)
    {
        ActionBase* currAction = m_LiveActions[x];
        if (currAction->m_bActive)
        {
            m_LiveActions[x]->Update(deltaTime);
        }
    }

    // Check for new actions.
    if (deltaTime > (m_fBulletTimeStamp + m_fBulletTimer) && 
        Core::g_InputManager.GetActionPressed(Core::InputMappings::eAction) &&
        !g_GameManager.GameIsPaused() && 
        !Core::g_InputManager.GetMouseClickObsorbedByUI())
    {
        m_fBulletTimeStamp = deltaTime;

        uint32_t equippedItemID = g_ItemManager.GetPrimaryWeaponID();
        const ItemData& currItemData = g_ItemManager.GetItemDataByID(equippedItemID);

        if (currItemData.m_ActionType == ActionType::eBullet)
        {
            CreateNewBullet(g_Player.GetPlayerRectangle());
        }
        else
        {
            CreateNewMelee(g_Player.GetPlayerRectangle(), deltaTime);
        }

    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerAction::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, g_GameGlobals.COLOR_WHITE.r, g_GameGlobals.COLOR_WHITE.g, g_GameGlobals.COLOR_WHITE.b, g_GameGlobals.COLOR_WHITE.a);
    SDL_RenderFillRect(renderer, &m_AimIndicator);

    const uint8_t uiLiveActionSize = static_cast<uint8_t>(m_LiveActions.size());
    for (uint8_t x = 0; x < uiLiveActionSize; ++x)
    {
        ActionBase* currAction = m_LiveActions[x];
        if (currAction->m_bActive)
        {
            m_LiveActions[x]->Draw(renderer);
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerAction::InitializeActions()
{
    g_EventManager.Subscribe(Events::eDayNightChanged, [this]() { PlayerAction::OnDayNightChangedEvent(); });
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerAction::ResetPlayerActions()
{
    m_LiveActions.clear();
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerAction::CreateNewBullet(SDL_Rect& currRect)
{
    uint32_t uiAmmoID = Core::StringToHash32(std::string("itm_Ammo"));
    const ItemData& ammoInventoryItem = g_ItemManager.GetItemDataByID(uiAmmoID);
    if (ammoInventoryItem.m_uiAmount > 0)
    {
        g_Player.ShootAmmo();

        ActionBase* newBullet = new BulletAction;
        newBullet->SetPosition(currRect.x, currRect.y);
        newBullet->SetDirection(g_Player.m_PlayerMovement.GetDirection());

        m_LiveActions.push_back(newBullet);

        g_SoundManager.PlaySoundByID(ARROW_SOUND_ID);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerAction::CreateNewMelee(SDL_Rect& currRect, float deltaTime)
{
    MeleeAction* newMelee = new MeleeAction;
    newMelee->SetInitialTime(deltaTime);

    m_LiveActions.push_back(newMelee);

    g_SoundManager.PlaySoundByID(HAMMER_SOUND_ID);
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerAction::UpdateAimIndicator()
{
    const int iOffset = 25;
    
    const SDL_Rect& playerRect = g_Player.GetPlayerRectangle();
    Direction currDirection = g_Player.m_PlayerMovement.GetDirection();

    if (currDirection == Direction::eLeft)
    {
        m_AimIndicator.x = playerRect.x - iOffset;
        m_AimIndicator.y = playerRect.y + ((playerRect.h / 2) - (m_AimIndicator.h / 2));
    }
    else if (currDirection == Direction::eUp)
    {
        m_AimIndicator.x = playerRect.x + ((playerRect.w / 2) - (m_AimIndicator.w / 2));
        m_AimIndicator.y = playerRect.y - iOffset;
    }
    else if (currDirection == Direction::eDown)
    {
        m_AimIndicator.x = playerRect.x + ((playerRect.w / 2) - (m_AimIndicator.w / 2));
        m_AimIndicator.y = playerRect.y + playerRect.h + iOffset;
    }
    else
    {
        m_AimIndicator.x = playerRect.x + playerRect.w + iOffset;
        m_AimIndicator.y = playerRect.y +  ((playerRect.w / 2) - (m_AimIndicator.w / 2));
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerAction::OnDayNightChangedEvent()
{
    m_LiveActions.clear();
}

}