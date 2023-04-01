#include "UICoreTypes.h"
#include "../Managers/InputManager.h"
#include "../Managers/SettingsManager.h"
#include "../Systems/Hash.h"
#include "GameGlobals.h"
#include "../Utility/Utility.h"
#include "Game/Managers/AssetManager.h"

#define DEFAULT_TEXTBLOCK_ID "DEFAULT"

namespace UI
{


// -------------------------------------------------------
// -------------------------------------------------------
UIBase::UIBase()
{
    m_BaseRectangle.x = 0;
    m_BaseRectangle.y = 0;
    m_BaseRectangle.w = 100;
    m_BaseRectangle.h = 100;

    m_vOffset.m_X = 0;
    m_vOffset.m_Y = 0;

    m_Visibility = UIVisibility::eVisible;

    m_Anchor = Anchor::eTopLeft;
    m_Alignment = Anchor::eTopLeft;

    m_uiMouseState = 0;

    m_Color = Florida::g_GameGlobals.COLOR_BLACK;

    m_bStyleSet = false;
}


// -------------------------------------------------------
// -------------------------------------------------------
UIBase::~UIBase()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIBase::Update()
{
    // Update Mouse State.
    int iMouseX = 0;
    int iMouseY = 0;

    SDL_GetMouseState(&iMouseX, &iMouseY);

    // Update button state.
    if (Core::Utility::CollisionBetweenPointAndRectangle(m_BaseRectangle, Core::Vec2i(iMouseX, iMouseY)))
    {
        // Hover
        m_uiMouseState |= MouseState::eHover;

        // LMouse
        if (Core::g_InputManager.GetActionPressed(Core::InputMappings::eMouse1))
        {
            m_uiMouseState |= MouseState::eLMouse;
        }
        else
        {
            m_uiMouseState &= ~MouseState::eLMouse;
        }

        // RMouse
        if (Core::g_InputManager.GetActionPressed(Core::InputMappings::eMouse2))
        {
            m_uiMouseState |= MouseState::eRMouse;
        }
        else
        {
            m_uiMouseState &= ~MouseState::eRMouse;
        }
    }
    else
    {
        m_uiMouseState &= ~MouseState::eHover;
        m_uiMouseState &= ~MouseState::eLMouse;
        m_uiMouseState &= ~MouseState::eLMouse;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIBase::RefreshUI()
{
    if (!m_bStyleSet)
    {
        SetStyle(Core::StringToHash32(std::string(DEFAULT_TEXTBLOCK_ID)));
    }

    const int iScreenWidth = Core::g_SettingsManager.GetScreenWidth();
    const int iScreenHeight = Core::g_SettingsManager.GetScreenHeight();

    // Set the base position based on Anchoring.
    switch (m_Anchor)
    {
    case UI::Anchor::eTopLeft: 
    {
        m_BaseRectangle.x = 0;
        m_BaseRectangle.y = 0;
        break;
    }
    case UI::Anchor::eTopCenter:
    {
        m_BaseRectangle.x = iScreenWidth / 2;
        m_BaseRectangle.y = 0;
        break;
    }
    case UI::Anchor::eTopRight:
    {
        m_BaseRectangle.x = iScreenWidth - m_BaseRectangle.w;
        m_BaseRectangle.y = 0;
        break;
    }
    case UI::Anchor::eCenterLeft:
    {
        m_BaseRectangle.x = 0;
        m_BaseRectangle.y = iScreenHeight / 2;
        break;
    }
    case UI::Anchor::eCenter:
    {
        m_BaseRectangle.x = iScreenWidth / 2;
        m_BaseRectangle.y = iScreenHeight / 2;
        break;
    }
    case UI::Anchor::eCenterRight:
    {
        m_BaseRectangle.x = iScreenWidth - m_BaseRectangle.w;
        m_BaseRectangle.y = iScreenHeight / 2;
        break;
    }
    case UI::Anchor::eBottomLeft:
    {
        m_BaseRectangle.x = 0;
        m_BaseRectangle.y = iScreenHeight - m_BaseRectangle.h;
        break;
    }
    case UI::Anchor::eBottomCenter:
    {
        m_BaseRectangle.x = iScreenWidth / 2;
        m_BaseRectangle.y = iScreenHeight - m_BaseRectangle.h;
        break;
    }
    case UI::Anchor::eBottomRight:
    {
        m_BaseRectangle.x = iScreenWidth - m_BaseRectangle.w;
        m_BaseRectangle.y = iScreenHeight - m_BaseRectangle.h;
        break;
    }
    default:
        break;
    }
 
    // Offset position based on Alignment.
    switch (m_Alignment)
    {
    case UI::Anchor::eTopCenter:
    {
        m_BaseRectangle.x -= (m_BaseRectangle.w / 2);
        break;
    }
    case UI::Anchor::eTopRight:
    {
        m_BaseRectangle.x -= m_BaseRectangle.w;
        break;
    }
    case UI::Anchor::eCenterLeft:
    {
        m_BaseRectangle.y -= (m_BaseRectangle.h / 2);
        break;
    }
    case UI::Anchor::eCenter:
    {
        m_BaseRectangle.x -= (m_BaseRectangle.w / 2);
        m_BaseRectangle.y -= (m_BaseRectangle.h / 2);
        break;
    }
    case UI::Anchor::eCenterRight:
    {
        m_BaseRectangle.x -= m_BaseRectangle.w;
        m_BaseRectangle.y -= (m_BaseRectangle.h / 2);
        break;
    }
    case UI::Anchor::eBottomLeft:
    {
        m_BaseRectangle.y -= m_BaseRectangle.h;
        break;
    }
    case UI::Anchor::eBottomCenter:
    {
        m_BaseRectangle.x -= (m_BaseRectangle.w / 2);
        m_BaseRectangle.y -= m_BaseRectangle.h;
        break;
    }
    case UI::Anchor::eBottomRight:
    {
        m_BaseRectangle.x -= m_BaseRectangle.w;
        m_BaseRectangle.y -= m_BaseRectangle.h;
        break;
    }
    case UI::Anchor::eTopLeft: 
    default:
        break;
    }

    // Offset position based on Offset.
    m_BaseRectangle.x += m_vOffset.m_X;
    m_BaseRectangle.y += m_vOffset.m_Y;

}


// -------------------------------------------------------
// -------------------------------------------------------
void UIBase::SetAnchor(Anchor anchor)
{
    m_Anchor = anchor;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIBase::SetAlignment(Anchor alignment)
{
    m_Alignment = alignment;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIBase::SetOffset(const int x, const int y)
{
    m_vOffset.m_X = x;
    m_vOffset.m_Y = y;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
TTF_Font* UIBase::GetDefaultFont()
{
    return Florida::g_AssetManager.m_FontAssets[Core::StringToHash32(std::string("fnt_Orbitron"))].m_Font;
}

}