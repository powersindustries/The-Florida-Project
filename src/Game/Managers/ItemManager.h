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
    uint32_t m_uiID;
    std::string m_sName;
    std::string m_sDescription;

    ItemType m_Type;
    ActionType m_ActionType;

    bool m_bDiscovered;
    uint8_t m_uiAmount;
};

class ItemManager
{
public:
    ItemManager();
    ~ItemManager();

    void Initialize();
    void ResetItemManager();

    const ItemData& GetItemDataByID(const uint32_t ItemID);

    bool AddItem(const uint32_t uiID, const uint32_t uiAmount);
    bool RemoveItem(const uint32_t uiID, const uint32_t uiAmount);

    inline void GetPrimaryWeaponID(const uint32_t uiID) { m_PrimaryWeapon = uiID; }
    inline void GetSecondaryWeaponID(const uint32_t uiID) { m_SecondaryWeapon = uiID; }
    inline uint32_t GetPrimaryWeaponID() const { return m_PrimaryWeapon; }
    inline uint32_t GetSecondaryWeaponID() const { return m_SecondaryWeapon; }

    inline const ItemData& GetLastAddedItemData() { return m_LastAddedItemData; }
    inline const std::vector<ItemData>& GetAllItemData() const { return m_ItemData; };


private:

    const ItemType StringToItemType(std::string string);
    const ActionType StringToActionItemType(std::string string);


private:

    std::string m_sItemsFilepath;

    uint32_t m_PrimaryWeapon;
    uint32_t m_SecondaryWeapon;

    ItemData m_LastAddedItemData;

    std::vector<ItemData> m_MasterItemData;

    std::vector<ItemData> m_ItemData;
    std::unordered_map<uint32_t, uint32_t> m_ItemDataMap; // ID hash, index to m_ItemData

};

extern ItemManager g_ItemManager;
}