#include "PlayerStatistics.h"
#include "Player.h"
#include "../Managers/EventManager.h"
#include "../Managers/GameplayManager.h"
#include "../Managers/SoundManager.h"
#include "Core/Systems/Logging.h"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
PlayerStatistics::PlayerStatistics()
{
    ResetPlayerStatistics();
}


// -------------------------------------------------------
// -------------------------------------------------------
PlayerStatistics::~PlayerStatistics()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerStatistics::InitializePlayerStatistics()
{
    g_EventManager.Subscribe(Events::eStaminaPotionUsed, [this]() { PlayerStatistics::OnStaminaPotionUsed(); });
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerStatistics::Update(float deltaTime)
{
    if (deltaTime >= (m_fTempTimestamp + m_fFramesToWait))
    {
        m_fTempTimestamp = deltaTime;

        UpdateStamina(deltaTime);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerStatistics::TakeDamage(uint8_t uiAmount)
{
    const int8_t iTempHealth = m_uiCurrHealth - uiAmount;

    if (iTempHealth <= 0)
    {
        // Dead.
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "PLAYER DIED!");
        g_GameplayManager.GameOver();
    }
    else
    {
        m_uiCurrHealth = iTempHealth;
        g_EventManager.Broadcast(Events::ePlayerHealthChanged);
    }

    g_SoundManager.PlaySoundByID("snd_PlayerDamage");
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerStatistics::Heal(uint8_t uiAmount)
{
    m_uiCurrHealth += uiAmount;
    g_EventManager.Broadcast(Events::ePlayerHealthChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerStatistics::DecreaseStamina(uint8_t uiAmount)
{
    const int8_t iTempStaminaDecrease = static_cast<int8_t>(m_iCurrStamina - uiAmount);
    if (iTempStaminaDecrease < 0)
    {
        m_iCurrStamina = 0;
    }
    else
    {
        m_iCurrStamina -= iTempStaminaDecrease;
    }

    m_StaminaStatus = EStaminaStatus::eRecharging;
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerStatistics::ResetPlayerStatistics()
{
    m_uiCurrHealth = m_uiMaxHealth;

    m_StaminaStatus = EStaminaStatus::eFull;
    m_iCurrStamina = m_iMaxStamina;
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerStatistics::UpdateStamina(float deltaTime)
{
    // Check Burnout timer
    if (m_StaminaStatus == EStaminaStatus::eBurnout && deltaTime <= (m_fTempBurnoutTimestamp + m_fStaminaBurnoutTime))
    {
        m_StaminaStatus = EStaminaStatus::eBurnout;
        return;
    }

    // Running Stamina use.
    if (g_Player.m_PlayerMovement.GetMovementState() == MovementState::eRunning)
    {
        if (m_iCurrStamina > 0)
        {
            m_StaminaStatus = EStaminaStatus::eUsing;
        }
        else
        {
            m_StaminaStatus = EStaminaStatus::eBurnout;
        }
    }
    else
    {
        const uint8_t uiTempStaminaAmount = m_iCurrStamina + m_uiStaminaRechargeAmount;

        if (m_iCurrStamina == m_iMaxStamina || uiTempStaminaAmount > m_iMaxStamina)
        {
            m_StaminaStatus = EStaminaStatus::eFull;
        }
        else
        {
            m_StaminaStatus = EStaminaStatus::eRecharging;
        }
    }

    switch (m_StaminaStatus)
    {
    case Florida::EStaminaStatus::eFull:
    {
        m_iCurrStamina = m_iMaxStamina;
        break;
    }
    case Florida::EStaminaStatus::eUsing:
    {
        m_iCurrStamina -= m_uiUsingStaminaAmount;
        break;
    }
    case Florida::EStaminaStatus::eRecharging:
    {
        m_iCurrStamina += m_uiStaminaRechargeAmount;
        break;
    }
    case Florida::EStaminaStatus::eBurnout:
    {
        m_iCurrStamina = 0;
        m_fTempBurnoutTimestamp = deltaTime;
        break;
    }
    default:
        break;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerStatistics::OnStaminaPotionUsed()
{
    m_StaminaStatus = EStaminaStatus::eFull;
    m_iCurrStamina = m_iMaxStamina;
}

}