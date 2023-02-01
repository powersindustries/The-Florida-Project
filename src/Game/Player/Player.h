#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>

#include "PlayerMovement.h"
#include "PlayerInventory.h"
#include "PlayerStatistics.h"
#include "PlayerAction.h"
#include "Core/Types/Sprite.h"

using namespace CoreTypes;

namespace Florida
{


struct InteractState
{
    bool m_bHeld = false;
    float m_fTime = 0.0f;
};


class Player
{
public:
    Player();
    ~Player();

    void InitializePlayer();

    void Update(float* deltaTime);
    void Draw(SDL_Renderer* renderer);

    // Base.
    SDL_Rect& GetPlayerRectangle() { return m_PlayerRectangle; }
    void SetPlayerRectangle(SDL_Rect rectangle) { m_PlayerRectangle = rectangle; }

    void SetPlayerPosition(int x, int y);
    inline void SetPlayerPositionX(int x) { m_PlayerRectangle.x = x; };
    inline void SetPlayerPositionY(int y) { m_PlayerRectangle.y = y; };

    inline const InteractState& GetInteractState() { return m_InteractState; };

    // Movement.
    inline const MovementState& GetMovementState() const { return m_PlayerMovement.m_State; };
    inline const Direction& GetDirection() const { return m_PlayerMovement.m_Direction; };

    inline void SetHaultMovement(bool bHault) { m_PlayerMovement.SetHaultMovement(bHault); };

    // Inventory.
    const std::vector<InventoryItemData>& GetPlayerInventoryAll() const;

    void AddItemToInventory(const uint32_t idHash, const uint32_t amount);
    void RemoveItemFromInventory(const uint32_t idHash, const uint32_t amount);

    inline uint32_t GetPrimaryEquippedItemID() { return m_PlayerInventory.m_PrimaryEquippedItem; }
    inline uint32_t GetSecondaryEquippedItemID() { return m_PlayerInventory.m_SecondaryEquippedItem; }

    inline const InventoryItemData GetLastAddedInventoryItemData() { return m_PlayerInventory.m_LastAddedInventoryItemData; }
    InventoryItemData& GetPlayerInventoryDataByID(uint32_t uiItemID);

    void ShootAmmo();

    // Statistics.
    inline const int8_t& GetCurrHealth() { return m_PlayerStatistics.m_uiCurrHealth; }
    inline const int8_t& GetMaxHealth() { return m_PlayerStatistics.m_uiMaxHealth; }

    inline const int8_t& GetCurrStamina() { return m_PlayerStatistics.m_iCurrStamina; }
    inline const int8_t& GetMaxStamina() { return m_PlayerStatistics.m_iMaxStamina; }

    inline const EStaminaStatus GetStaminaStatus() { return m_PlayerStatistics.m_StaminaStatus; }

    void TakeDamage(uint8_t uiAmount);
    void Heal(uint8_t uiAmount);
    void DecreaseStamina(uint8_t uiAmount);

    void ResetPlayer();


private:

    void InitializePlayerSprite();
    void InitializePlayerInventory();

    void SwapPrimarySecondaryEquipment();

    void UseStaminaPotion();
    
    void OnDayNightChangedEvent();


private:

    InteractState m_InteractState;

    PlayerMovement m_PlayerMovement;
    PlayerInventory m_PlayerInventory;
    PlayerAction m_PlayerAction;
    PlayerStatistics m_PlayerStatistics;

    std::string m_sPlayerFilepath;
    std::string m_sInventoryFilepath;
    std::string m_sInventoryFilepath2;

    SDL_Rect m_PlayerRectangle;

    Sprite* m_PlayerSprite;

};

extern Player g_Player;
}