#include "ItemManager.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>

#include "Core/Systems/Hash.h"
#include "Core/Systems/Logging.h"

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
void ItemManager::LoadItems()
{
    rapidxml::file<> xmlFile(m_sItemsFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* texturesNode = doc.first_node("Items");
    for (rapidxml::xml_node<>* child = texturesNode->first_node(); child; child = child->next_sibling())
    {
        ItemData itemData;
        itemData.m_sID = child->first_attribute("ID")->value();
        itemData.m_sName = child->first_attribute("Name")->value();
        itemData.m_sDescription = child->first_attribute("Description")->value();
        itemData.m_uiIDHash = CoreSystems::StringToHash32(itemData.m_sID);
        itemData.m_Type = StringToItemType(child->first_attribute("Type")->value());
        itemData.m_ActionType = StringToActionItemType(child->first_attribute("ActionType")->value());

        m_ItemData.push_back(itemData);

        const uint32_t uiItemDataSize = static_cast<uint32_t>(m_ItemData.size()) - 1;
        m_ItemDataMap.insert({ itemData.m_uiIDHash, uiItemDataSize });

    }

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Items Load Complete!");
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