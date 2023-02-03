#include "Player.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>

#include "Core/Systems/Systems.h"
#include "Core/Managers/InputManager.h"
#include "../Managers/EventManager.h"
#include "../Managers/GameManager.h"

#define HAMMER_ID "itm_Hammer"
#define GUN_ID "itm_Gun"
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
    m_sPlayerFilepath.append("/src/Data/Player.xml");

    m_sInventoryFilepath.append(__PROJECT_DIRECTORY__);
    m_sInventoryFilepath.append("/src/Data/Inventory.xml");

    m_sInventoryFilepath2.append(__PROJECT_DIRECTORY__);
    m_sInventoryFilepath2.append("/src/Data/Inventory2.xml");
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
    InitializePlayerInventory();
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

    if (CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eInteract))
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
    if (CoreManagers::g_InputManager.GetActionPressed(CoreManagers::InputMappings::eSwitchEquipment))
    {
        SwapPrimarySecondaryEquipment();
    }

    // Use Stamina Potion on R key.
    if (CoreManagers::g_InputManager.GetActionPressed(CoreManagers::InputMappings::eReload))
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
const std::vector<InventoryItemData>& Player::GetPlayerInventoryAll() const
{
    return m_PlayerInventory.m_Inventory;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::AddItemToInventory(const uint32_t idHash, const uint32_t amount)
{
    m_PlayerInventory.AddItemToInventory(idHash, amount);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::RemoveItemFromInventory(const uint32_t idHash, const uint32_t amount)
{
    m_PlayerInventory.RemoveItemFromInventory(idHash, amount);
}


// -------------------------------------------------------
// -------------------------------------------------------
Florida::InventoryItemData& Player::GetPlayerInventoryDataByID(uint32_t uiItemID)
{
    const uint32_t uiInventoryIndex = m_PlayerInventory.m_InventoryMap[uiItemID];
    return m_PlayerInventory.m_Inventory[uiInventoryIndex];
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::ShootAmmo()
{
    m_PlayerInventory.UseAmmo();
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
    m_PlayerInventory.ResetPlayerInventory();
    m_PlayerAction.ResetPlayerActions();
    m_PlayerStatistics.ResetPlayerStatistics();

    m_PlayerInventory.m_PrimaryEquippedItem = CoreSystems::StringToHash32(std::string(HAMMER_ID));
    m_PlayerInventory.m_SecondaryEquippedItem = CoreSystems::StringToHash32(std::string(GUN_ID));

    g_EventManager.Broadcast(Events::ePlayerPrimaryEquippedItemChanged);
    g_EventManager.Broadcast(Events::ePlayerSecondaryEquippedItemChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::InitializePlayerSprite()
{
    rapidxml::file<> xmlFile(m_sPlayerFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());


    // Initialize/Load Player Sprite
    rapidxml::xml_node<>* playerNode = doc.first_node("Player");
    std::string sTextureId = playerNode->first_attribute("Texture")->value();
    int iSpeed = std::atoi(playerNode->first_attribute("Speed")->value());

    m_PlayerSprite = new Sprite(CoreSystems::StringToHash32(sTextureId), iSpeed);


    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Player Sprite Initialization Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::InitializePlayerInventory()
{
    rapidxml::file<> xmlFile(m_sInventoryFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* inventoryNode = doc.first_node("Inventory");
    for (rapidxml::xml_node<>* child = inventoryNode->first_node(); child; child = child->next_sibling())
    {
        std::string sItemId = child->first_attribute("ID")->value();
        int iAmount = std::atoi(child->first_attribute("Amount")->value());

        m_PlayerInventory.AddItemToInventory(CoreSystems::StringToHash32(sItemId), iAmount);
    }

    m_PlayerInventory.SetMasterInventory();
    m_PlayerInventory.m_PrimaryEquippedItem = CoreSystems::StringToHash32(std::string(HAMMER_ID));
    m_PlayerInventory.m_SecondaryEquippedItem = CoreSystems::StringToHash32(std::string(GUN_ID));

    g_EventManager.Broadcast(Events::ePlayerPrimaryEquippedItemChanged);
    g_EventManager.Broadcast(Events::ePlayerSecondaryEquippedItemChanged);

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Player Inventory Initialization Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::SwapPrimarySecondaryEquipment()
{
    const uint32_t uiPrimaryWeapon = m_PlayerInventory.m_PrimaryEquippedItem;
    m_PlayerInventory.m_PrimaryEquippedItem = m_PlayerInventory.m_SecondaryEquippedItem;
    m_PlayerInventory.m_SecondaryEquippedItem = uiPrimaryWeapon;

    g_EventManager.Broadcast(Events::ePlayerPrimaryEquippedItemChanged);
    g_EventManager.Broadcast(Events::ePlayerSecondaryEquippedItemChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::UseStaminaPotion()
{
    m_PlayerInventory.UseStaminaPotion();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Player::OnDayNightChangedEvent()
{
    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Player Actions deleted.");

    m_PlayerAction.m_LiveActions.clear();
}

}