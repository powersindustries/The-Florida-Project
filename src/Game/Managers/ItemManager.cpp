#include "ItemManager.h"

#include "Core/Systems/Hash.h"
#include "Core/Systems/Logging.h"
#include "Core/Utility/Utility.h"
#include "Core/Types/LuaTableLoader.h"
#include "GameManager.h"
#include "EventManager.h"
#include "SoundManager.h"

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
    m_sItemsFilepath.append("/src/Data/Items.lua");
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
	Core::LuaTableLoader* luaLoader = new Core::LuaTableLoader(m_sItemsFilepath);

	// Load Textures table.
	luaLoader->LoadTableByID("Items");

	const uint8_t uiItemTableSize = luaLoader->GetCurrentTableSize();
	for (uint8_t x = 0; x < uiItemTableSize; ++x)
	{
		int indexOffset = x + 1;

		if (luaLoader->PushIntegerAndGetTable(indexOffset))
		{
			break;
		}

        ItemData itemData;
        itemData.m_uiID = Core::StringToHash32(luaLoader->GetStringByID("ID"));
        itemData.m_sName = luaLoader->GetStringByID("Name");
        itemData.m_sDescription = luaLoader->GetStringByID("Description");
        itemData.m_Type = StringToItemType(luaLoader->GetStringByID("Type"));
        itemData.m_ActionType = StringToActionItemType(luaLoader->GetStringByID("ActionType"));
        itemData.m_bDiscovered = Core::Utility::StringToBool(luaLoader->GetStringByID("Discovered"));
        itemData.m_uiAmount = static_cast<uint8_t>(luaLoader->GetIntByID("Amount"));

        m_ItemData.push_back(itemData);

        const uint32_t uiItemDataSize = static_cast<uint32_t>(m_ItemData.size()) - 1;
        m_ItemDataMap.insert({ itemData.m_uiID, uiItemDataSize });

		luaLoader->PopTopTableElement();
    }

    delete luaLoader;

    m_MasterItemData = m_ItemData;

    m_PrimaryWeapon = Core::StringToHash32(std::string(HAMMER_ID));
    m_SecondaryWeapon = Core::StringToHash32(std::string(GUN_ID));

    g_EventManager.Broadcast(Events::ePlayerPrimaryEquippedItemChanged);
    g_EventManager.Broadcast(Events::ePlayerSecondaryEquippedItemChanged);

    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Items Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void ItemManager::ResetItemManager()
{
    m_ItemData = m_MasterItemData;

    m_PrimaryWeapon = Core::StringToHash32(std::string(HAMMER_ID));
    m_SecondaryWeapon = Core::StringToHash32(std::string(GUN_ID));

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
        Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "The item you're trying to add does not exist.");
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
        Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "The item you're trying to remove does not exist.");
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
const ItemType ItemManager::StringToItemType(std::string string)
{
    if (string == "resource")
    {
        return ItemType::eResource;
    }
    else if (string == "tool")
    {
        return ItemType::eTool;
    }
    else if (string == "weapon")
    {
        return ItemType::eWeapon;
    }
    else if (string == "disposable")
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
const Florida::ActionType ItemManager::StringToActionItemType(std::string string)
{
    if (string == "melee")
    {
        return ActionType::eMelee;
    }
    else if (string == "bullet")
    {
        return ActionType::eBullet;
    }
    else
    {
        return ActionType::eNone;
    }
}

}