#include "Player.h"

#include "Core/Systems/Systems.h"
#include "Core/Managers/InputManager.h"
#include "Core/Types/LuaTableLoader.h"
#include "../Managers/EventManager.h"
#include "../Managers/GameManager.h"
#include "../Managers/ItemManager.h"

#define HAMMER_ID "itm_Hammer"
#define GUN_ID "itm_Gun"
#define AMMO_ID "itm_Ammo"
#define STAMINA_POTION_ID "itm_StaminaPotion"
#define PLAYER_WIDTHHEIGHT 32

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
Player g_Player;


// -------------------------------------------------------
// -------------------------------------------------------
Player::Player()
    : m_PlayerSprite(nullptr)
{
    m_PlayerRectangle.w = PLAYER_WIDTHHEIGHT;
    m_PlayerRectangle.h = PLAYER_WIDTHHEIGHT;

    m_sPlayerFilepath.append(__PROJECT_DIRECTORY__);
    m_sPlayerFilepath.append("/src/Data/Player.lua");
}


// -------------------------------------------------------
// -------------------------------------------------------
Player::~Player()
{
    delete m_PlayerSprite;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::InitializePlayer()
{
    InitializePlayerSprite();
    m_PlayerAction.InitializeActions();
    m_PlayerStatistics.InitializePlayerStatistics();

    g_EventManager.Subscribe(Events::eDayNightChanged, [this]() { Player::OnDayNightChangedEvent(); });
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::Update(float deltaTime)
{
    m_PlayerStatistics.Update(deltaTime);
    m_PlayerMovement.Update(deltaTime);
    m_PlayerAction.Update(deltaTime);

    m_PlayerSprite->Update(deltaTime, m_PlayerRectangle);

    if (Core::g_InputManager.GetActionHeld(Core::InputMappings::eInteract))
    {
        // Reset held timer.
        if (m_InteractState.m_fTime == 0.0f)
        {
            m_InteractState.m_fTime = deltaTime;
        }

        m_InteractState.m_bHeld = true;
    }
    else
    {
        m_InteractState.m_bHeld = false;
        m_InteractState.m_fTime = 0.0f;
    }

    // Change weapons on Q key.
    if (Core::g_InputManager.GetActionPressed(Core::InputMappings::eSwitchEquipment))
    {
        SwapPrimarySecondaryEquipment();
    }

    // Use Stamina Potion on R key.
    if (Core::g_InputManager.GetActionPressed(Core::InputMappings::eReload))
    {
        UseStaminaPotion();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::Draw(SDL_Renderer* renderer)
{
    m_PlayerSprite->Draw(renderer, m_PlayerMovement.m_Direction == Direction::eRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);
    m_PlayerAction.Draw(renderer);

    if (g_GameManager.GraphicsDebugModeOn())
    {
        // Draw Debug Rectangle
        SDL_SetRenderDrawColor(renderer, g_GameGlobals.COLOR_BLACK.r, g_GameGlobals.COLOR_BLACK.g, g_GameGlobals.COLOR_BLACK.b, g_GameGlobals.COLOR_BLACK.a);
        SDL_RenderFillRect(renderer, &m_PlayerRectangle);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::SetPlayerPosition(int x, int y)
{
    m_PlayerRectangle.x = x;
    m_PlayerRectangle.y = y;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::ShootAmmo()
{
    g_ItemManager.RemoveItem(Core::StringToHash32(std::string(AMMO_ID)), 1);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::TakeDamage(uint8_t uiAmount)
{
    m_PlayerStatistics.TakeDamage(uiAmount);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::Heal(uint8_t uiAmount)
{
    m_PlayerStatistics.Heal(uiAmount);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::DecreaseStamina(uint8_t uiAmount)
{
    m_PlayerStatistics.DecreaseStamina(uiAmount);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::ResetPlayer()
{
    m_PlayerAction.ResetPlayerActions();
    m_PlayerStatistics.ResetPlayerStatistics();

    g_EventManager.Broadcast(Events::ePlayerPrimaryEquippedItemChanged);
    g_EventManager.Broadcast(Events::ePlayerSecondaryEquippedItemChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::InitializePlayerSprite()
{
	LuaTableLoader* luaLoader = new LuaTableLoader(m_sPlayerFilepath);

	luaLoader->LoadTableByID("Player");


    // Initialize/Load Player Sprite
    std::string sTextureId = luaLoader->GetStringByID("Texture");
    int iSpeed = luaLoader->GetIntByID("Speed");

    m_PlayerSprite = new Sprite(Core::StringToHash32(sTextureId), iSpeed);

    delete luaLoader;

    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Player Sprite Initialization Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::SwapPrimarySecondaryEquipment()
{
    const uint32_t uiPrimaryWeapon = g_ItemManager.GetPrimaryWeaponID();
    const uint32_t uiSecondaryWeapon = g_ItemManager.GetSecondaryWeaponID();

    g_ItemManager.GetPrimaryWeaponID(uiSecondaryWeapon);
    g_ItemManager.GetSecondaryWeaponID(uiPrimaryWeapon);

    g_EventManager.Broadcast(Events::ePlayerPrimaryEquippedItemChanged);
    g_EventManager.Broadcast(Events::ePlayerSecondaryEquippedItemChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::UseStaminaPotion()
{
    g_ItemManager.RemoveItem(Core::StringToHash32(std::string(STAMINA_POTION_ID)), 1);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::OnDayNightChangedEvent()
{
    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Player Actions deleted.");

    m_PlayerAction.m_LiveActions.clear();
}

}