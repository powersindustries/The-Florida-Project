#include "PlayerMovement.h"
#include "Player.h"
#include "../Managers/MapManager.h"
#include "Core/Managers/InputManager.h"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
PlayerMovement::PlayerMovement()
{
    m_State = MovementState::eIdle;
    m_Direction = Direction::eRight;
}


// -------------------------------------------------------
// -------------------------------------------------------
PlayerMovement::~PlayerMovement()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerMovement::Update(float deltaTime)
{
    switch (m_State)
    {
    case MovementState::eIdle:
    {
        if (CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eLeft) || 
            CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eRight) ||
            CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eUp) ||
            CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eDown)
            )
        {
            m_State = MovementState::eMoving;
        }
        break;
    }
    case MovementState::eMoving:
    case MovementState::eRunning:
    {
        // Check if movement has stopped. If it has, set state to IDLE and early out.
        if (!CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eUp) &&
            !CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eDown) &&
            !CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eLeft) &&
            !CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eRight))
        {
            m_State = MovementState::eIdle;
            return;
        }

        // Check to see if running.
        if (CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eRun))
        {
            m_State = MovementState::eRunning;
        }
        else
        {
            m_State = MovementState::eMoving;
        }

        // Set Direction.
        int64_t iTempInputManagerTimestamp = -1;

        if (CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eLeft) &&
            CoreManagers::g_InputManager.GetActionHeldTimestamp(CoreManagers::InputMappings::eLeft) > iTempInputManagerTimestamp)
        {
            m_Direction = Direction::eLeft;
            iTempInputManagerTimestamp = CoreManagers::g_InputManager.GetActionHeldTimestamp(CoreManagers::InputMappings::eLeft);
        }

        if (CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eRight) &&
            CoreManagers::g_InputManager.GetActionHeldTimestamp(CoreManagers::InputMappings::eRight) > iTempInputManagerTimestamp)
        {
            m_Direction = Direction::eRight;
            iTempInputManagerTimestamp = CoreManagers::g_InputManager.GetActionHeldTimestamp(CoreManagers::InputMappings::eRight);
        }

        if (CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eUp) &&
            CoreManagers::g_InputManager.GetActionHeldTimestamp(CoreManagers::InputMappings::eUp) > iTempInputManagerTimestamp)
        {
            m_Direction = Direction::eUp;
            iTempInputManagerTimestamp = CoreManagers::g_InputManager.GetActionHeldTimestamp(CoreManagers::InputMappings::eUp);
        }

        if (CoreManagers::g_InputManager.GetActionHeld(CoreManagers::InputMappings::eDown) &&
            CoreManagers::g_InputManager.GetActionHeldTimestamp(CoreManagers::InputMappings::eDown) > iTempInputManagerTimestamp)
        {
            m_Direction = Direction::eDown;
            iTempInputManagerTimestamp = CoreManagers::g_InputManager.GetActionHeldTimestamp(CoreManagers::InputMappings::eDown);
        }

        // Set Speed value.
        uint8_t uiSpeedOffset = m_uiPlayerSpeed;
        if (g_Player.GetStaminaStatus() == EStaminaStatus::eBurnout)
        {
            uiSpeedOffset /= 2;
        }
        else if (m_State == MovementState::eRunning)
        {
            uiSpeedOffset *= 2;
        }

        // Move Player.
        SDL_Rect& playerRect = g_Player.GetPlayerRectangle();
        if (g_MapManager.CollisionStoppingMovement(playerRect, m_Direction))
        {
            m_State = MovementState::eIdle;
            return;
        }
        else if (m_Direction == Direction::eUp)
        {
            g_Player.SetPlayerPositionY(playerRect.y - uiSpeedOffset);
        }
        else if (m_Direction == Direction::eDown)
        {
            g_Player.SetPlayerPositionY(playerRect.y + uiSpeedOffset);
        }
        else if (m_Direction == Direction::eLeft)
        {
            g_Player.SetPlayerPositionX(playerRect.x - uiSpeedOffset);
        }
        else if (m_Direction == Direction::eRight)
        {
            g_Player.SetPlayerPositionX(playerRect.x + uiSpeedOffset);
        }

        break;
    }
    case MovementState::eHault:
    {
        return;
    }
    default:
    {
        break;
    }
    }

}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerMovement::Draw(SDL_Renderer* renderer)
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void PlayerMovement::SetHaultMovement(bool bHault)
{
    if (bHault)
    {
        m_State = MovementState::eHault;
    }
    else
    {
        m_State = MovementState::eIdle;
    }
}

}