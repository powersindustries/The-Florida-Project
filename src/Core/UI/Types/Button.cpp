#include "Button.h"
#include "GameGlobals.h"
#include "Core/Game.h"
#include "Game/Managers/AssetManager.h"
#include "Core/Systems/Systems.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/Managers/InputManager.h"

namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
Button::Button()
    : m_Font(nullptr), m_MessageTexture(nullptr)
{
    m_FontRectangle.x = 0;
    m_FontRectangle.y = 0;
    m_FontRectangle.w = 80;
    m_FontRectangle.h = 15;

    m_uiButtonStateFlags = 0;

    m_TextAlignment = HorizontalAlignment::eCenter;
    m_BaseColor = Florida::g_GameGlobals.COLOR_BLACK;
    m_HoverColor = Florida::g_GameGlobals.COLOR_GRAY;

    m_iData1 = 0;
    m_iData2 = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
Button::~Button()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::Update()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::Update(CoreManagers::InputManager& inputManager)
{
    // Dont update button if hidden or disabled.
    if (m_DisplayType == DisplayType::eHidden || m_DisplayType == DisplayType::eDisabled)
    {
        return;
    }


    int mouseX = 0;
    int mouseY = 0;

    SDL_GetMouseState(&mouseX, &mouseY);

    // Update button state.
    if (MouseCollisionDetected(mouseX, mouseY))
    {
        // Hover
        m_uiButtonStateFlags |= ButtonStates::eHover;

        // LMouse
        if (inputManager.GetActionPressed(CoreManagers::InputMappings::eMouse1))
        {
            m_uiButtonStateFlags |= ButtonStates::eLMouse;

            CoreManagers::g_InputManager.SetMouseClickObsorbedByUI(true);
        }
        else
        {
            m_uiButtonStateFlags &= ~ButtonStates::eLMouse;
        }

        // RMouse
        if (inputManager.GetActionPressed(CoreManagers::InputMappings::eMouse2))
        {
            m_uiButtonStateFlags |= ButtonStates::eRMouse;
        }
        else
        {
            m_uiButtonStateFlags &= ~ButtonStates::eRMouse;
        }
    }
    else
    {
        m_uiButtonStateFlags &= ~ButtonStates::eHover;
        m_uiButtonStateFlags &= ~ButtonStates::eLMouse;
        m_uiButtonStateFlags &= ~ButtonStates::eLMouse;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::Draw(SDL_Renderer* renderer)
{
    if (m_DisplayType == DisplayType::eHidden)
    {
        return;
    }

    if (MouseHovered())
    {
        SDL_SetRenderDrawColor(renderer,
            m_HoverColor.r,
            m_HoverColor.g,
            m_HoverColor.b,
            m_HoverColor.a);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer,
            m_BaseColor.r,
            m_BaseColor.g,
            m_BaseColor.b,
            m_DisplayType == DisplayType::eVisible ? m_BaseColor.a : (m_BaseColor.a / 2) );
    }

    SDL_RenderFillRect(renderer, &m_BaseRectangle);

    SDL_RenderCopy(renderer, m_MessageTexture, NULL, &m_FontRectangle);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetPosition(int x, int y)
{
    m_AnchorType = AlignmentType::ePoint;

    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;

    m_FontRectangle.x = x;
    m_FontRectangle.y = y;
    
    m_Anchor.m_Horizontal = HorizontalAlignment::eLeft;
    m_Anchor.m_Vertical = VerticalAlignment::eTop;
    m_vOffset.m_iX = 0;
    m_vOffset.m_iY = 0;
    
    RefreshInternalUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetFont(uint32_t fontIDHash)
{
    m_Font = Florida::g_AssetManager.m_FontAssets[fontIDHash].m_Font;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetSize(int width, int height)
{
    m_BaseRectangle.w = width;
    m_BaseRectangle.h = height;

    RefreshUI();
    RefreshInternalUI();
}

// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetText(std::string text)
{
    m_Text = text;

    RefreshInternalUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetTextAlignment(HorizontalAlignment alignment)
{
    m_TextAlignment = alignment;

    RefreshInternalUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::RefreshUI()
{
    // Set Anchor position.
    int iCenterX = CoreManagers::g_SettingsManager.GetScreenWidth() / 2;
    int iRightX  = CoreManagers::g_SettingsManager.GetScreenWidth();

    int iCenterY = CoreManagers::g_SettingsManager.GetScreenHeight() / 2;
    int iBottomY = CoreManagers::g_SettingsManager.GetScreenHeight();

    if (m_AnchorType == AlignmentType::eAnchored)
    {
        // Set x-index position based on Anchor.
        switch (m_Anchor.m_Horizontal)
        {
        case HorizontalAlignment::eLeft:
        {
            m_BaseRectangle.x = m_vOffset.m_iX;
            break;
        }
        case HorizontalAlignment::eCenter:
        {
            m_BaseRectangle.x = iCenterX + m_vOffset.m_iX;
            break;
        }
        case HorizontalAlignment::eRight:
        {
            m_BaseRectangle.x = iRightX - m_vOffset.m_iX - GetWidth();
            break;
        }
        default:
            break;
        }

        // Set y-index position based on Anchor.
        switch (m_Anchor.m_Vertical)
        {
        case VerticalAlignment::eTop:
        {
            m_BaseRectangle.y = m_vOffset.m_iY;
            break;
        }
        case VerticalAlignment::eCenter:
        {
            m_BaseRectangle.y = iCenterY + m_vOffset.m_iY;
            break;
        }
        case VerticalAlignment::eBottom:
        {
            m_BaseRectangle.y = iBottomY - m_vOffset.m_iY - GetHeight();
            break;
        }
        default:
            break;
        }
    }

    // Set x offset based on Element Alignment.
    switch (m_ElementAlignment.m_Horizontal)
    {
    case HorizontalAlignment::eLeft:
    {
        break;
    }
    case HorizontalAlignment::eCenter:
    {
        m_BaseRectangle.x -= (m_BaseRectangle.w / 2);
        break;
    }
    case HorizontalAlignment::eRight:
    {
        m_BaseRectangle.x -= m_BaseRectangle.w;
        break;
    }
    default:
        break;
    }

    // Set y offset based on Element Alignment.
    switch (m_ElementAlignment.m_Vertical)
    {
    case VerticalAlignment::eTop:
    {
        break;
    }
    case VerticalAlignment::eCenter:
    {
        m_BaseRectangle.y -= (m_BaseRectangle.h / 2);
        break;
    }
    case VerticalAlignment::eBottom:
    {
        m_BaseRectangle.y -= m_BaseRectangle.h;
        break;
    }
    default:
        break;
    }

    RefreshInternalUI();

}


// -------------------------------------------------------
// -------------------------------------------------------
bool Button::MouseCollisionDetected(int mouseX, int mouseY)
{
    return !((mouseX < m_BaseRectangle.x)
        || (mouseX > m_BaseRectangle.x + m_BaseRectangle.w)
        || (mouseY < m_BaseRectangle.y)
        || (mouseY > m_BaseRectangle.y + m_BaseRectangle.h));
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::RefreshInternalUI()
{
    if (!m_Font)
    {
        SetFont(CoreSystems::StringToHash32(std::string("fnt_Charriot")));
    }

    SDL_Surface* surface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), Florida::g_GameGlobals.COLOR_WHITE);

    SDL_DestroyTexture(m_MessageTexture);
    m_MessageTexture = SDL_CreateTextureFromSurface(Florida::Game::m_Renderer, surface);

    SDL_FreeSurface(surface);

    // Set Texture dimensions
    SDL_Point textureSize;
    SDL_QueryTexture(m_MessageTexture, NULL, NULL, &textureSize.x, &textureSize.y);
    m_FontRectangle.w = textureSize.x;
    m_FontRectangle.h = textureSize.y;

    // Reset Location
    switch (m_TextAlignment)
    {
    case HorizontalAlignment::eLeft:
    {
        m_FontRectangle.x = m_BaseRectangle.x;
        m_FontRectangle.y = m_BaseRectangle.y + ((m_BaseRectangle.h - m_FontRectangle.h) / 2);
        break;
        break;
    }
    case HorizontalAlignment::eCenter:
    {
        m_FontRectangle.x = m_BaseRectangle.x + ((m_BaseRectangle.w - m_FontRectangle.w) / 2);
        m_FontRectangle.y = m_BaseRectangle.y + ((m_BaseRectangle.h - m_FontRectangle.h) / 2);
        break;
    }
    case HorizontalAlignment::eRight:
    {
        m_FontRectangle.x = (m_BaseRectangle.x + m_BaseRectangle.w) - m_FontRectangle.w;
        m_FontRectangle.y = m_BaseRectangle.y + ((m_BaseRectangle.h - m_FontRectangle.h) / 2);
        break;
    }
    }
}

}