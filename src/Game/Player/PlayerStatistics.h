#pragma once
#include <SDL.h> // SDL Main

namespace Florida
{

enum class EStaminaStatus
{
    eFull,          // No stamina being used. Player is not moving or walking.
    eUsing,         // Stamina being used currently.
    eRecharging,    // Stamina recharging.
    eBurnout        // All stamina has been used. Player moves slower for a given time period.
};

class PlayerStatistics
{
public:
    PlayerStatistics();
    ~PlayerStatistics();

    void InitializePlayerStatistics();
    void Update(float deltaTime);

    void TakeDamage(uint8_t uiAmount);
    void Heal(uint8_t uiAmount);

    void DecreaseStamina(uint8_t uiAmount);

    void ResetPlayerStatistics();

    inline const int8_t& GetCurrHealth() const { return m_uiCurrHealth; }
    inline const int8_t& GetMaxHealth() { return m_uiMaxHealth; }
    inline const int8_t& GetCurrStamina() const { return m_iCurrStamina; }
    inline const int8_t& GetMaxStamina() { return m_iMaxStamina; }

    inline EStaminaStatus GetStaminaStatus() { return m_StaminaStatus; }


private:

    void UpdateStamina(float deltaTime);

    void OnStaminaPotionUsed();


private:

    const int8_t m_uiMaxHealth = 3;
    int8_t m_uiCurrHealth;

    EStaminaStatus m_StaminaStatus;

    const int8_t m_iMaxStamina = 100;;
    int8_t m_iCurrStamina;

    const float m_fFramesToWait = 0.1f;
    float m_fTempTimestamp = 0.0;

    float m_fTempBurnoutTimestamp = 0.0f;
    const float m_fStaminaBurnoutTime = 3.0f;

    const uint8_t m_uiStaminaRechargeAmount = 8;
    const uint8_t m_uiUsingStaminaAmount = 5;


private:

    friend class Player;

};

}