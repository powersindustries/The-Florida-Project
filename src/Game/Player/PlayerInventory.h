#pragma once
#include <vector>
#include <unordered_map>

namespace Florida
{


struct InventoryItemData
{
    uint32_t m_uiID;
    uint32_t m_uiAmount;
};


class PlayerInventory
{
public:
    PlayerInventory();
    ~PlayerInventory();

    void SetMasterInventory();

    void AddItemToInventory(const uint32_t idHash, const uint32_t amount);
    void RemoveItemFromInventory(const uint32_t idHash, const uint32_t amount);
    
    inline void SetPrimaryEquippedItem(const uint32_t uiID) { m_PrimaryEquippedItem = uiID; };
    inline void SetSecondaryEquippedItem(const uint32_t uiID) { m_SecondaryEquippedItem = uiID; };

    void UseAmmo();
    void UseStaminaPotion();
    void ResetPlayerInventory();


private:

    std::vector<InventoryItemData> m_MasterInventory;

    std::vector<InventoryItemData> m_Inventory;
    std::unordered_map<uint32_t, uint32_t> m_InventoryMap;

    uint32_t m_PrimaryEquippedItem;
    uint32_t m_SecondaryEquippedItem;

    InventoryItemData m_LastAddedInventoryItemData;


private:

    friend class Player;

};

}