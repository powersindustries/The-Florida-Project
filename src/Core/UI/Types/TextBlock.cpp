#include "TextBlock.h"
#include "GameGlobals.h"
#include "Core/Game.h"

#include "Game/Managers/AssetManager.h"
#include "Core/Systems/Systems.h"
#include "Core/Managers/SettingsManager.h"

namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
TextBlock::TextBlock()
    : m_Font(nullptr), m_MessageTexture(nullptr)
{
    m_Color = Florida::g_GameGlobals.COLOR_BLACK;
}


// -------------------------------------------------------
// -------------------------------------------------------
TextBlock::~TextBlock()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::Update()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::Draw(SDL_Renderer* renderer)
{
    if (m_DisplayType == DisplayType::eHidden)
    {
        return;
    }

    SDL_RenderCopy(renderer, m_MessageTexture, NULL, &m_BaseRectangle);
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetPosition(int x, int y)
{
    m_AnchorType = AlignmentType::ePoint;

    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;

    m_Anchor.m_Horizontal = HorizontalAlignment::eLeft;
    m_Anchor.m_Vertical = VerticalAlignment::eTop;
    m_vOffset.m_iX = 0;
    m_vOffset.m_iY = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::RefreshUI()
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
void TextBlock::SetText(std::string text)
{
    if (!m_Font)
    {
        SetFont(CoreSystems::StringToHash32(std::string("fnt_Charriot")));
    }

    m_Text = text;

    SDL_Surface* surface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), m_Color);

    SDL_DestroyTexture(m_MessageTexture);
    m_MessageTexture = SDL_CreateTextureFromSurface(Florida::Game::m_Renderer, surface);

    SDL_FreeSurface(surface);

    SDL_Point textureSize;
    SDL_QueryTexture(m_MessageTexture, NULL, NULL, &textureSize.x, &textureSize.y);
    m_BaseRectangle.w = textureSize.x;
    m_BaseRectangle.h = textureSize.y;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetSize(int width, int height)
{
    m_BaseRectangle.w = width;
    m_BaseRectangle.h = height;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetFont(uint32_t fontIDHash)
{
    m_Font = Florida::g_AssetManager.m_FontAssets[fontIDHash].m_Font;
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetColor(SDL_Color color)
{
    if (!m_Font)
    {
        SetFont(CoreSystems::StringToHash32(std::string("fnt_Charriot")));
    }

    m_Color = color;

    SDL_Surface* surface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), m_Color);

    SDL_DestroyTexture(m_MessageTexture);
    m_MessageTexture = SDL_CreateTextureFromSurface(Florida::Game::m_Renderer, surface);

    SDL_FreeSurface(surface);
}

}