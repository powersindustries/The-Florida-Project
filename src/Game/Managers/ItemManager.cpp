#include "ItemManager.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>

#include "Core/Systems/Hash.h"
#include "Core/Systems/Logging.h"
#include "GameManager.h"
#include "EventManager.h"
#include "SoundManager.h"
#include "Core/Utility/Utility.h"

#define ITEM_ADDED_SOUND "snd_ItemAdded"
#define HAMMER_ID "itm_Hammer"
#define GUN_ID "itm_Gun"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
ItemManager g_ItemManager;


// -------------------------------------------------------
// -------------------------------------------------------
ItemManager::ItemManager()
{
    m_sItemsFilepath.append(__PROJECT_DIRECTORY__);
    m_sItemsFilepath.append("/src/Data/Items.xml");
}


// -------------------------------------------------------
// -------------------------------------------------------
ItemManager::~ItemManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void ItemManager::InitializeItemManager()
{
    rapidxml::file<> xmlFile(m_sItemsFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* texturesNode = doc.first_node("Items");
    for (rapidxml::xml_node<>* child = texturesNode->first_node(); child; child = child->next_sibling())
    {
        ItemData itemData;
        itemData.m_uiID = CoreSystems::StringToHash32(std::string(child->first_attribute("ID")->value()));
        itemData.m_sName = child->first_attribute("Name")->value();
        itemData.m_sDescription = child->first_attribute("Description")->value();
        itemData.m_Type = StringToItemType(child->first_attribute("Type")->value());
        itemData.m_ActionType = StringToActionItemType(child->first_attribute("ActionType")->value());
        itemData.m_bDiscovered = CoreUtility::Utility::StringToBool(std::string(child->first_attribute("Discovered")->value()));
        itemData.m_uiAmount = static_cast<uint8_t>(std::stoi(child->first_attribute("Amount")->value()));

        m_ItemData.push_back(itemData);

        const uint32_t uiItemDataSize = static_cast<uint32_t>(m_ItemData.size()) - 1;
        m_ItemDataMap.insert({ itemData.m_uiID, uiItemDataSize });

    }

    m_MasterItemData = m_ItemData;

    m_PrimaryWeapon = CoreSystems::StringToHash32(std::string(HAMMER_ID));
    m_SecondaryWeapon = CoreSystems::StringToHash32(std::string(GUN_ID));

    g_EventManager.Broadcast(Events::ePlayerPrimaryEquippedItemChanged);
    g_EventManager.Broadcast(Events::ePlayerSecondaryEquippedItemChanged);

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Items Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void ItemManager::ResetItemManager()
{
    m_ItemData = m_MasterItemData;

    m_PrimaryWeapon = CoreSystems::StringToHash32(std::string(HAMMER_ID));
    m_SecondaryWeapon = CoreSystems::StringToHash32(std::string(GUN_ID));

    g_EventManager.Broadcast(Events::ePlayerPrimaryEquippedItemChanged);
    g_EventManager.Broadcast(Events::ePlayerSecondaryEquippedItemChanged);
    g_EventManager.Broadcast(Events::eInventoryChanged);
    g_EventManager.Broadcast(Events::eAmmoChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
const Florida::ItemData& ItemManager::GetItemDataByID(const uint32_t ItemID)
{
    const uint32_t uiItemIndex = m_ItemDataMap[ItemID];
    return m_ItemData[uiItemIndex];
}


// -------------------------------------------------------
// -------------------------------------------------------
bool ItemManager::AddItem(const uint32_t uiID, const uint32_t uiAmount)
{
    if (m_ItemDataMap.find(uiID) == m_ItemDataMap.end())
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "The item you're trying to add does not exist.");
        return false;
    }
    else
    {
        const uint32_t uiItemIndex = m_ItemDataMap[uiID];
        ItemData& currItemData = m_ItemData[uiItemIndex];
        currItemData.m_uiAmount += uiAmount;
    }

    m_LastAddedItemData.m_uiID = uiID;
    m_LastAddedItemData.m_uiAmount = uiAmount;

    if (g_GameManager.IntroSeen())
    {
        g_SoundManager.PlaySoundByID(ITEM_ADDED_SOUND);
    }

    g_EventManager.Broadcast(Events::eInventoryChanged);

    return true;
}


// -------------------------------------------------------
// -------------------------------------------------------
bool ItemManager::RemoveItem(const uint32_t uiID, const uint32_t uiAmount)
{
    if (m_ItemDataMap.find(uiID) == m_ItemDataMap.end())
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "The item you're trying to remove does not exist.");
        return false;
    }
    else
    {
        const uint32_t uiItemIndex = m_ItemDataMap[uiID];
        ItemData& currItemData = m_ItemData[uiItemIndex];

        int iTempAmount = currItemData.m_uiAmount - uiAmount;
        if (iTempAmount >= 0)
        {
            currItemData.m_uiAmount = iTempAmount;
        }
        else
        {
            currItemData.m_uiAmount = 0;
        }
    }

    g_EventManager.Broadcast(Events::eInventoryChanged);

    return true;
}


// -------------------------------------------------------
// -------------------------------------------------------
const ItemType ItemManager::StringToItemType(const char* string)
{
    if (strcmp(string, "resource") == 0)
    {
        return ItemType::eResource;
    }
    else if (strcmp(string, "tool") == 0)
    {
        return ItemType::eTool;
    }
    else if (strcmp(string, "weapon") == 0)
    {
        return ItemType::eWeapon;
    }
    else if (strcmp(string, "disposable") == 0)
    {
        return ItemType::eDisposable;
    }
    else
    {
        return ItemType::eNONE;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
const Florida::ActionType ItemManager::StringToActionItemType(const char* string)
{
    if (strcmp(string, "melee") == 0)
    {
        return ActionType::eMelee;
    }
    else if (strcmp(string, "bullet") == 0)
    {
        return ActionType::eBullet;
    }
    else
    {
        return ActionType::eNone;
    }
}

}