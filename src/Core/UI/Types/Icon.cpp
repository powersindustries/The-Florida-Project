#include "Icon.h"
#include "GameGlobals.h"
#include "Core/Managers/SettingsManager.h"

namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
Icon::Icon()
    : m_Sprite(nullptr)
{
    m_Color = Florida::g_GameGlobals.COLOR_RED;
}


// -------------------------------------------------------
// -------------------------------------------------------
Icon::Icon(uint32_t uiTextureID)
    : m_Sprite(nullptr)
{
    m_Color = Florida::g_GameGlobals.COLOR_RED;

    m_Sprite = new CoreTypes::Sprite(uiTextureID, CoreTypes::SpriteType::eNonAnimated);
}


// -------------------------------------------------------
// -------------------------------------------------------
Icon::~Icon()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Icon::Update()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Icon::Draw(SDL_Renderer* renderer)
{
    if (m_DisplayType == DisplayType::eHidden)
    {
        return;
    }

    if (m_Sprite)
    {
        m_Sprite->Draw(renderer);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b, m_DisplayType == DisplayType::eVisible ? m_Color.a : (m_Color.a / 2));
        SDL_RenderFillRect(renderer, &m_BaseRectangle);
    }

}


// -------------------------------------------------------
// -------------------------------------------------------
void Icon::SetPosition(int x, int y)
{
    m_AnchorType = AlignmentType::ePoint;

    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;

    m_Anchor.m_Horizontal = HorizontalAlignment::eLeft;
    m_Anchor.m_Vertical = VerticalAlignment::eTop;
    m_vOffset.m_iX = 0;
    m_vOffset.m_iY = 0;

    m_Sprite->SetPosition(m_BaseRectangle);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Icon::RefreshUI()
{
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
            m_BaseRectangle.x = (CoreManagers::g_SettingsManager.GetScreenWidth() / 2) + m_vOffset.m_iX;
            break;
        }
        case HorizontalAlignment::eRight:
        {
            m_BaseRectangle.x = CoreManagers::g_SettingsManager.GetScreenWidth() - m_vOffset.m_iX - GetWidth();
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
            m_BaseRectangle.y = (CoreManagers::g_SettingsManager.GetScreenHeight() / 2) + m_vOffset.m_iY;
            break;
        }
        case VerticalAlignment::eBottom:
        {
            m_BaseRectangle.y = CoreManagers::g_SettingsManager.GetScreenHeight() - m_vOffset.m_iY - GetHeight();
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
}


// -------------------------------------------------------
// -------------------------------------------------------
void Icon::SetSize(int width, int height)
{
    m_BaseRectangle.w = width;
    m_BaseRectangle.h = height;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Icon::SetTexture(uint32_t uiTextureID)
{
    m_Sprite = new CoreTypes::Sprite(uiTextureID, CoreTypes::SpriteType::eNonAnimated);
    m_Sprite->SetPosition(m_BaseRectangle);
}

}