#include "InputManager.h"
#include "Game/Managers/GameManager.h"

#define DEFAULT_TIMESTAMP -1

namespace CoreManagers
{


// -------------------------------------------------------
// -------------------------------------------------------
InputManager g_InputManager;


// -------------------------------------------------------
// -------------------------------------------------------
InputManager::InputManager()
    : m_SDLEvent(nullptr)
{
    m_SDLEvent = new SDL_Event;

    m_bMouseClickObsorbedByUI = false;
}


// -------------------------------------------------------
// -------------------------------------------------------
InputManager::~InputManager()
{
    delete m_SDLEvent;
}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::ProcessInputs()
{
    ResetAllPressedData();

    while (SDL_PollEvent(m_SDLEvent))
    {
        switch (m_SDLEvent->type)
        {
        case SDL_QUIT:
        {
            Florida::g_GameManager.SetGameRunning(false);
            break;
        }
        case SDL_KEYDOWN:
        {
            OnKeyDownEvent();
            break;
        }
        case SDL_KEYUP:
        {
            OnKeyUpEvent();
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEMOTION:
        {
            OnMouseEvent();
            break;
        }
        default:
            break;
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
bool InputManager::GetActionPressed(const InputMappings Mapping)
{
    switch (Mapping)
    {
    case InputMappings::eMouse1:
    {
        return m_InputMappingPressedData.m_LeftClicked;
    }
    case InputMappings::eMouse2:
    {
        return m_InputMappingPressedData.m_RightClicked;
    }
    case InputMappings::eMouse3:
    {
        return m_InputMappingPressedData.m_MiddleClicked;
    }
    case InputMappings::eMouseMotion:
    {
        return m_InputMappingPressedData.m_MouseMotion;
    }
    case InputMappings::eESCMenu:
    {
        return m_InputMappingPressedData.m_Escape;
    }
    case InputMappings::eTabMenu:
    {
        return m_InputMappingPressedData.m_Tab;
    }
    case InputMappings::eRight:
    {
        return m_InputMappingPressedData.m_D || m_InputMappingPressedData.m_RightArrow;
    }
    case InputMappings::eLeft:
    {
        return m_InputMappingPressedData.m_A || m_InputMappingPressedData.m_LeftArrow;
    }
    case InputMappings::eUp:
    {
        return m_InputMappingPressedData.m_W || m_InputMappingPressedData.m_UpArrow;
    }
    case InputMappings::eDown:
    {
        return m_InputMappingPressedData.m_S || m_InputMappingPressedData.m_DownArrow;
    }
    case InputMappings::eRun:
    {
        return m_InputMappingPressedData.m_Space;
    }
    case InputMappings::eInteract:
    {
        return m_InputMappingPressedData.m_E;
    }
    case InputMappings::eAction:
    {
        return m_InputMappingPressedData.m_LeftClicked || m_InputMappingPressedData.m_J;
    }
    case InputMappings::eSwitchEquipment:
    {
        return m_InputMappingPressedData.m_Q;
    }
    case InputMappings::eReload:
    {
        return m_InputMappingPressedData.m_R;
    }
    case InputMappings::eDebug1:
    {
        return m_InputMappingPressedData.m_F1;
    }
    case InputMappings::eDebug2:
    {
        return m_InputMappingPressedData.m_F2;
    }
    case InputMappings::eDebug3:
    {
        return m_InputMappingPressedData.m_F3;
    }
    case InputMappings::eDebug4:
    {
        return m_InputMappingPressedData.m_F4;
    }
    default:
    {
        return false;
    }
    }
}


bool InputManager::GetActionHeld(const InputMappings Mapping)
{
    switch (Mapping)
    {
    case InputMappings::eMouse1:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_LeftClicked;
    }
    case InputMappings::eMouse2:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_RightClicked;
    }
    case InputMappings::eMouse3:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_MiddleClicked;
    }
    case InputMappings::eMouseMotion:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_MouseMotion;
    }
    case InputMappings::eESCMenu:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_Escape;
    }
    case InputMappings::eTabMenu:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_Tab;
    }
    case InputMappings::eRight:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_D || m_InputMappingHeldData.m_InputMappingData.m_RightArrow;
    }
    case InputMappings::eLeft:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_A || m_InputMappingHeldData.m_InputMappingData.m_LeftArrow;
    }
    case InputMappings::eUp:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_W || m_InputMappingHeldData.m_InputMappingData.m_UpArrow;
    }
    case InputMappings::eDown:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_S || m_InputMappingHeldData.m_InputMappingData.m_DownArrow;
    }
    case InputMappings::eRun:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_Space;
    }
    case InputMappings::eInteract:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_E;
    }
    case InputMappings::eAction:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_LeftClicked || m_InputMappingHeldData.m_InputMappingData.m_J;
    }
    case InputMappings::eSwitchEquipment:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_Q;
    }
    case InputMappings::eReload:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_R;
    }
    case InputMappings::eDebug1:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_F1;
    }
    case InputMappings::eDebug2:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_F2;
    }
    case InputMappings::eDebug3:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_F3;
    }
    case InputMappings::eDebug4:
    {
        return m_InputMappingHeldData.m_InputMappingData.m_F4;
    }
    default:
    {
        return false;
    }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
int64_t InputManager::GetActionHeldTimestamp(const InputMappings Mapping)
{
    switch (Mapping)
    {
    case InputMappings::eMouse1:
    {
        return m_InputMappingHeldData.m_LeftClickedStamp;
    }
    case InputMappings::eMouse2:
    {
        return m_InputMappingHeldData.m_RightClickedStamp;
    }
    case InputMappings::eMouse3:
    {
        return m_InputMappingHeldData.m_MiddleClickedStamp;
    }
    case InputMappings::eESCMenu:
    {
        return m_InputMappingHeldData.m_EscapeStamp;
    }
    case InputMappings::eTabMenu:
    {
        return m_InputMappingHeldData.m_TabStamp;
    }
    case InputMappings::eRight:
    {
        return m_InputMappingHeldData.m_DStamp > m_InputMappingHeldData.m_RightArrowStamp ? m_InputMappingHeldData.m_DStamp : m_InputMappingHeldData.m_RightArrowStamp;
    }
    case InputMappings::eLeft:
    {
        return m_InputMappingHeldData.m_AStamp > m_InputMappingHeldData.m_LeftArrowStamp ? m_InputMappingHeldData.m_AStamp : m_InputMappingHeldData.m_LeftArrowStamp;
    }
    case InputMappings::eUp:
    {
        return m_InputMappingHeldData.m_WStamp > m_InputMappingHeldData.m_UpArrowStamp ? m_InputMappingHeldData.m_WStamp : m_InputMappingHeldData.m_UpArrowStamp;
    }
    case InputMappings::eDown:
    {
        return m_InputMappingHeldData.m_SStamp > m_InputMappingHeldData.m_DownArrowStamp ? m_InputMappingHeldData.m_SStamp : m_InputMappingHeldData.m_DownArrowStamp;
    }
    case InputMappings::eRun:
    {
        return m_InputMappingHeldData.m_SpaceStamp;
    }
    case InputMappings::eInteract:
    {
        return m_InputMappingHeldData.m_EStamp;
    }
    case InputMappings::eAction:
    {
        return m_InputMappingHeldData.m_LeftClickedStamp != DEFAULT_TIMESTAMP ? m_InputMappingHeldData.m_LeftClickedStamp : m_InputMappingHeldData.m_JStamp;
    }
    case InputMappings::eSwitchEquipment:
    {
        return m_InputMappingHeldData.m_QStamp;
    }
    case InputMappings::eReload:
    {
        return m_InputMappingHeldData.m_RStamp;
    }
    case InputMappings::eDebug1:
    {
        return m_InputMappingHeldData.m_F1Stamp;
    }
    case InputMappings::eDebug2:
    {
        return m_InputMappingHeldData.m_F2Stamp;
    }
    case InputMappings::eDebug3:
    {
        return m_InputMappingHeldData.m_F3Stamp;
    }
    case InputMappings::eDebug4:
    {
        return m_InputMappingHeldData.m_F4Stamp;
    }
    default:
    {
        return false;
    }
    }

}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::ResetAllPressedData()
{
    m_InputMappingPressedData.m_F1 = false;
    m_InputMappingPressedData.m_F2 = false;
    m_InputMappingPressedData.m_F3 = false;
    m_InputMappingPressedData.m_F4 = false;
    m_InputMappingPressedData.m_LeftClicked = false;
    m_InputMappingPressedData.m_RightClicked = false;
    m_InputMappingPressedData.m_MiddleClicked = false;
    m_InputMappingPressedData.m_MouseMotion = false;
    m_InputMappingPressedData.m_Escape = false;
    m_InputMappingPressedData.m_Tab = false;
    m_InputMappingPressedData.m_UpArrow = false;
    m_InputMappingPressedData.m_DownArrow = false;
    m_InputMappingPressedData.m_LeftArrow = false;
    m_InputMappingPressedData.m_RightArrow = false;
    m_InputMappingPressedData.m_Space = false;
    m_InputMappingPressedData.m_W = false;
    m_InputMappingPressedData.m_A = false;
    m_InputMappingPressedData.m_S = false;
    m_InputMappingPressedData.m_D = false;
    m_InputMappingPressedData.m_E = false;
    m_InputMappingPressedData.m_J = false;
    m_InputMappingPressedData.m_Q = false;
    m_InputMappingPressedData.m_R = false;

    m_bMouseClickObsorbedByUI = false;
}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::OnKeyUpEvent()
{
    SDL_KeyboardEvent& currKeyboardEvent = m_SDLEvent->key;
    switch (currKeyboardEvent.keysym.sym)
    {
    case SDLK_ESCAPE:
    {
        m_InputMappingHeldData.m_InputMappingData.m_Escape = false;
        m_InputMappingHeldData.m_EscapeStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_TAB:
    {
        m_InputMappingHeldData.m_InputMappingData.m_Tab = false;
        m_InputMappingHeldData.m_TabStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_F1:
    {
        m_InputMappingHeldData.m_InputMappingData.m_F1 = false;
        m_InputMappingHeldData.m_F1Stamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_F2:
    {
        m_InputMappingHeldData.m_InputMappingData.m_F2 = false;
        m_InputMappingHeldData.m_F2Stamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_F3:
    {
        m_InputMappingHeldData.m_InputMappingData.m_F3 = false;
        m_InputMappingHeldData.m_F3Stamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_F4:
    {
        m_InputMappingHeldData.m_InputMappingData.m_F4 = false;
        m_InputMappingHeldData.m_F4Stamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_UP:
    {
        m_InputMappingHeldData.m_InputMappingData.m_UpArrow = false;
        m_InputMappingHeldData.m_UpArrowStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_DOWN:
    {
        m_InputMappingHeldData.m_InputMappingData.m_DownArrow = false;
        m_InputMappingHeldData.m_DownArrowStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_LEFT:
    {
        m_InputMappingHeldData.m_InputMappingData.m_LeftArrow = false;
        m_InputMappingHeldData.m_LeftArrowStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_RIGHT:
    {
        m_InputMappingHeldData.m_InputMappingData.m_RightArrow = false;
        m_InputMappingHeldData.m_RightArrowStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_SPACE:
    {
        m_InputMappingHeldData.m_InputMappingData.m_Space = false;
        m_InputMappingHeldData.m_SpaceStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_w:
    {
        m_InputMappingHeldData.m_InputMappingData.m_W = false;
        m_InputMappingHeldData.m_WStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_a:
    {
        m_InputMappingHeldData.m_InputMappingData.m_A = false;
        m_InputMappingHeldData.m_AStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_s:
    {
        m_InputMappingHeldData.m_InputMappingData.m_S = false;
        m_InputMappingHeldData.m_SStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_d:
    {
        m_InputMappingHeldData.m_InputMappingData.m_D = false;
        m_InputMappingHeldData.m_DStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_e:
    {
        m_InputMappingHeldData.m_InputMappingData.m_E = false;
        m_InputMappingHeldData.m_EStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_j:
    {
        m_InputMappingHeldData.m_InputMappingData.m_J = false;
        m_InputMappingHeldData.m_JStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_q:
    {
        m_InputMappingHeldData.m_InputMappingData.m_Q = false;
        m_InputMappingHeldData.m_QStamp = DEFAULT_TIMESTAMP;
        break;
    }
    case SDLK_r:
    {
        m_InputMappingHeldData.m_InputMappingData.m_R = false;
        m_InputMappingHeldData.m_RStamp = DEFAULT_TIMESTAMP;
        break;
    }
    }

}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::OnMouseEvent()
{
    SDL_MouseButtonEvent& mouseButtonEvent = m_SDLEvent->button;
    m_InputMappingPressedData.m_LeftClicked = mouseButtonEvent.button == SDL_BUTTON_LEFT;
    m_InputMappingPressedData.m_RightClicked = mouseButtonEvent.button == SDL_BUTTON_RIGHT;
    m_InputMappingPressedData.m_MiddleClicked = mouseButtonEvent.button == SDL_BUTTON_MIDDLE;
    m_InputMappingHeldData.m_InputMappingData.m_LeftClicked = mouseButtonEvent.button == SDL_BUTTON_LEFT;
    m_InputMappingHeldData.m_InputMappingData.m_RightClicked = mouseButtonEvent.button == SDL_BUTTON_RIGHT;
    m_InputMappingHeldData.m_InputMappingData.m_MiddleClicked = mouseButtonEvent.button == SDL_BUTTON_MIDDLE;

    SDL_MouseMotionEvent& mouseMotionEvent = m_SDLEvent->motion;
    int32_t xRel = static_cast<int32_t>(mouseMotionEvent.xrel);
    int32_t yRel = static_cast<int32_t>(mouseMotionEvent.yrel);

    uint32_t xRelAbs = static_cast<int32_t>(abs(mouseMotionEvent.xrel));
    uint32_t yRelAbs = static_cast<int32_t>(abs(mouseMotionEvent.yrel));

    m_InputMappingPressedData.m_MouseMotion = (xRelAbs > 1 && yRelAbs > 1);
    m_InputMappingHeldData.m_InputMappingData.m_MouseMotion = (xRelAbs > 1 && yRelAbs > 1);
    if (m_InputMappingPressedData.m_MouseMotion)
    {
        if (xRelAbs == yRelAbs)
        {
            m_MouseMotionData.m_iMotionX = 0;
            m_MouseMotionData.m_iMotionY = 0;
        }
        // Movement in X.
        else if (xRelAbs > yRelAbs)
        {
            m_MouseMotionData.m_iMotionX = xRel;
            m_MouseMotionData.m_iMotionY = 0;
        }
        // Movement in X.
        else
        {
            m_MouseMotionData.m_iMotionX = 0;
            m_MouseMotionData.m_iMotionY = yRel;
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void InputManager::OnKeyDownEvent()
{
    SDL_KeyboardEvent& keyboardEvent = m_SDLEvent->key;

    if (keyboardEvent.repeat == 0)
    {
        switch (keyboardEvent.keysym.sym)
        {
        case SDLK_ESCAPE:
        {
            m_InputMappingPressedData.m_Escape = true;

            m_InputMappingHeldData.m_InputMappingData.m_Escape = true;
            if (m_InputMappingHeldData.m_EscapeStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_EscapeStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_TAB:
        {
            m_InputMappingPressedData.m_Tab = true;

            m_InputMappingHeldData.m_InputMappingData.m_Tab = true;
            if (m_InputMappingHeldData.m_TabStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_TabStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_F1:
        {
            m_InputMappingPressedData.m_F1 = true;

            m_InputMappingHeldData.m_InputMappingData.m_F1 = true;
            if (m_InputMappingHeldData.m_F1Stamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_F1Stamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_F2:
        {
            m_InputMappingPressedData.m_F2 = true;

            m_InputMappingHeldData.m_InputMappingData.m_F2 = true;
            if (m_InputMappingHeldData.m_F2Stamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_F2Stamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_F3:
        {
            m_InputMappingPressedData.m_F3 = true;

            m_InputMappingHeldData.m_InputMappingData.m_F3 = true;
            if (m_InputMappingHeldData.m_F3Stamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_F3Stamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_F4:
        {
            m_InputMappingPressedData.m_F4 = true;

            m_InputMappingHeldData.m_InputMappingData.m_F4 = true;
            if (m_InputMappingHeldData.m_F4Stamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_F4Stamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_UP:
        {
            m_InputMappingPressedData.m_UpArrow = true;
            m_InputMappingHeldData.m_InputMappingData.m_UpArrow = true;
            if (m_InputMappingHeldData.m_UpArrowStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_UpArrowStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_DOWN:
        {
            m_InputMappingPressedData.m_DownArrow = true;

            m_InputMappingHeldData.m_InputMappingData.m_DownArrow = true;
            if (m_InputMappingHeldData.m_DownArrowStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_DownArrowStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_LEFT:
        {
            m_InputMappingPressedData.m_LeftArrow = true;

            m_InputMappingHeldData.m_InputMappingData.m_LeftArrow = true;
            if (m_InputMappingHeldData.m_LeftArrowStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_LeftArrowStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_RIGHT:
        {
            m_InputMappingPressedData.m_RightArrow = true;

            m_InputMappingHeldData.m_InputMappingData.m_RightArrow = true;
            if (m_InputMappingHeldData.m_RightArrowStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_RightArrowStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_SPACE:
        {
            m_InputMappingPressedData.m_Space = true;

            m_InputMappingHeldData.m_InputMappingData.m_Space = true;
            if (m_InputMappingHeldData.m_SpaceStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_SpaceStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_w:
        {
            m_InputMappingPressedData.m_W = true;

            m_InputMappingHeldData.m_InputMappingData.m_W = true;
            if (m_InputMappingHeldData.m_WStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_WStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_a:
        {
            m_InputMappingPressedData.m_A = true;

            m_InputMappingHeldData.m_InputMappingData.m_A = true;
            if (m_InputMappingHeldData.m_AStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_AStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_s:
        {
            m_InputMappingPressedData.m_S = true;

            m_InputMappingHeldData.m_InputMappingData.m_S = true;
            if (m_InputMappingHeldData.m_SStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_SStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_d:
        {
            m_InputMappingPressedData.m_D = true;

            m_InputMappingHeldData.m_InputMappingData.m_D = true;
            if (m_InputMappingHeldData.m_DStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_DStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_e:
        {
            m_InputMappingPressedData.m_E = true;

            m_InputMappingHeldData.m_InputMappingData.m_E = true;
            if (m_InputMappingHeldData.m_EStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_EStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_j:
        {
            m_InputMappingPressedData.m_J = true;

            m_InputMappingHeldData.m_InputMappingData.m_J = true;
            if (m_InputMappingHeldData.m_JStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_JStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_q:
        {
            m_InputMappingPressedData.m_Q = true;

            m_InputMappingHeldData.m_InputMappingData.m_Q = true;
            if (m_InputMappingHeldData.m_QStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_QStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        case SDLK_r:
        {
            m_InputMappingPressedData.m_R = true;

            m_InputMappingHeldData.m_InputMappingData.m_R = true;
            if (m_InputMappingHeldData.m_RStamp == DEFAULT_TIMESTAMP)
            {
                m_InputMappingHeldData.m_RStamp = m_SDLEvent->common.timestamp;
            }
            break;
        }
        }
    }
}

}