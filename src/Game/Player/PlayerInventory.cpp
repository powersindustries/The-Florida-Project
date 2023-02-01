#include "PlayerInventory.h"
#include "../Managers/EventManager.h"
#include "../Managers/SoundManager.h"
#include "../Managers/GameManager.h"
#include "Core/Systems/Hash.h"
#include "Core/Systems/Logging.h"

#define ITEM_ADDED_SOUND "snd_ItemAdded"
#define AMMO_ID "itm_Ammo"
#define STAMINAPOTION_ID "itm_StaminaPotion"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
PlayerInventory::PlayerInventory()
{
    m_PrimaryEquippedItem = 0;
    m_SecondaryEquippedItem = 0;

    m_LastAddedInventoryItemData.m_uiID = 0;
    m_LastAddedInventoryItemData.m_uiAmount = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
PlayerInventory::~PlayerInventory()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerInventory::SetMasterInventory()
{
    m_MasterInventory = m_Inventory;
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerInventory::AddItemToInventory(const uint32_t idHash, const uint32_t amount)
{
    if (m_InventoryMap.find(idHash) == m_InventoryMap.end())
    {
        InventoryItemData newInventoryData;
        newInventoryData.m_uiID = idHash;
        newInventoryData.m_uiAmount = amount;

        m_Inventory.push_back(newInventoryData);

        const uint32_t uiInventorySize = static_cast<uint32_t>(m_Inventory.size()) - 1;
        m_InventoryMap.insert( { idHash, uiInventorySize });
    }
    else
    {
        const uint32_t inventoryIndex = m_InventoryMap[idHash];
        m_Inventory[inventoryIndex].m_uiAmount += amount;
    }

    m_LastAddedInventoryItemData.m_uiID = idHash;
    m_LastAddedInventoryItemData.m_uiAmount = amount;

    if (g_GameManager.IntroSeen())
    {
        g_SoundManager.PlaySoundByID(ITEM_ADDED_SOUND);
    }

    g_EventManager.Broadcast(Events::eInventoryChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerInventory::RemoveItemFromInventory(const uint32_t idHash, const uint32_t amount)
{
    if (m_InventoryMap.find(idHash) == m_InventoryMap.end())
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "The item youre trying to remove does not exist.");
    }
    else
    {
        const uint32_t inventoryIndex = m_InventoryMap[idHash];
        InventoryItemData& removeItemData = m_Inventory[inventoryIndex];

        int tempAmountDifference = removeItemData.m_uiAmount - amount;
        if (tempAmountDifference >= 0)
        {
            removeItemData.m_uiAmount = tempAmountDifference;
        }
        else
        {
            removeItemData.m_uiAmount = 0;
        }
    }

    g_EventManager.Broadcast(Events::eInventoryChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerInventory::UseAmmo()
{
    uint32_t uiAmmoID = CoreSystems::StringToHash32(std::string(AMMO_ID));
    const uint32_t uiInventoryIndex = m_InventoryMap[uiAmmoID];
    InventoryItemData& ammoInventoryItem = m_Inventory[uiInventoryIndex];

    if (ammoInventoryItem.m_uiAmount > 0)
    {
        ammoInventoryItem.m_uiAmount--;

        g_EventManager.Broadcast(Events::eAmmoChanged);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerInventory::UseStaminaPotion()
{
    uint32_t uiStaminaID = CoreSystems::StringToHash32(std::string(STAMINAPOTION_ID));
    const uint32_t uiInventoryIndex = m_InventoryMap[uiStaminaID];
    InventoryItemData& staminaInventoryItem = m_Inventory[uiInventoryIndex];

    if (staminaInventoryItem.m_uiAmount > 0)
    {
        staminaInventoryItem.m_uiAmount--;

        g_EventManager.Broadcast(Events::eStaminaPotionUsed);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerInventory::ResetPlayerInventory()
{
    m_Inventory = m_MasterInventory;

    g_EventManager.Broadcast(Events::eInventoryChanged);
    g_EventManager.Broadcast(Events::eAmmoChanged);
}

}