#pragma once
#include <string>
#include <unordered_map>
#include "../Player/PlayerAction.h"

namespace Florida
{


enum class ItemType
{
    eResource = 0,
    eTool = 1,
    eWeapon = 2,
    eDisposable = 3,
    eNONE = 4
};


struct ItemData
{
    std::string m_sID;
    std::string m_sName;
    std::string m_sDescription;

    uint32_t m_uiIDHash;

    ItemType m_Type;
    ActionType m_ActionType;
};


class ItemManager
{
public:
    ItemManager();
    ~ItemManager();

    void LoadItems();

    const ItemData& GetItemDataByID(const uint32_t ItemID);


private:

    const ItemType StringToItemType(const char* string);
    const ActionType StringToActionItemType(const char* string);


public:

    std::vector<ItemData> m_ItemData;
    std::unordered_map<uint32_t, uint32_t> m_ItemDataMap; // ID hash, index to m_ItemData


private:

    std::string m_sItemsFilepath;

};

extern ItemManager g_ItemManager;
}