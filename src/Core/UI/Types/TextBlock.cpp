#include "TextBlock.h"
#include "GameGlobals.h"
#include "Core/Game.h"

#include "Core/Systems/Systems.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/Systems/Hash.h"
#include "Core/Managers/StyleManager.h"
#include "Game/Managers/AssetManager.h"

namespace UI
{


// -------------------------------------------------------
// -------------------------------------------------------
TextBlock::TextBlock()
    : m_Font(nullptr), m_MessageTexture(nullptr)
{
    m_Text = "";

    m_vSize.m_X = 0;
    m_vSize.m_Y = 0;

    m_uiWordWrap = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
TextBlock::~TextBlock()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::Draw(SDL_Renderer* renderer)
{
    if (m_Visibility == UIVisibility::eHidden)
    {
        return;
    }

    SDL_RenderCopy(renderer, m_MessageTexture, NULL, &m_BaseRectangle);
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetStyle(uint32_t uiStyleID)
{
    const Core::TextBlockStyle& currStyleData = Core::g_StyleManager.GetTextBlockStyle(uiStyleID);

    m_Font = Florida::g_AssetManager.m_FontAssets[currStyleData.m_uiFont].m_Font;
    m_Color = currStyleData.m_Color;

    if (m_Text == "")
    {
        m_Text = currStyleData.m_sDefaultText;
    }

    m_bStyleSet = true;

    CreateWordTexture();
    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetText(std::string text)
{
    m_Text = text;

    CreateWordTexture();
    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetVisibility(UIVisibility visibility)
{
    UIBase::SetVisibility(visibility);

    CreateWordTexture();
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetSize(const int x, const int y)
{
    m_vSize.m_X = x;
    m_vSize.m_Y = y;

    CreateWordTexture();
    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetWordWrap(uint8_t uiWordWrap)
{
    m_uiWordWrap = uiWordWrap;

    CreateWordTexture();
    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::SetPositionNoRefresh(const int x, const int y)
{
    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;
}


// -------------------------------------------------------
// -------------------------------------------------------
void TextBlock::CreateWordTexture()
{
    SDL_Color tempColor = 
    { 
    m_Color.r, 
    m_Color.g, 
    m_Color.b, 
    m_Visibility == UIVisibility::eVisible ? static_cast<Uint8>(m_Color.a) : static_cast<Uint8>(m_Color.a / 2)
    };

    SDL_Surface* surface = nullptr;
    if (m_Font)
    {
        if (m_uiWordWrap > 0)
        {
            surface = TTF_RenderText_Blended_Wrapped(m_Font, m_Text.c_str(), tempColor, m_uiWordWrap);
        }
        else
        {
            surface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), tempColor);
        }
    }
    else
    {
        if (m_uiWordWrap > 0)
        {
            surface = TTF_RenderText_Blended_Wrapped(GetDefaultFont(), m_Text.c_str(), tempColor, m_uiWordWrap);
        }
        else
        {
            surface = TTF_RenderText_Solid(GetDefaultFont(), m_Text.c_str(), tempColor);
        }
    }

    SDL_DestroyTexture(m_MessageTexture);
    m_MessageTexture = SDL_CreateTextureFromSurface(Florida::Game::m_Renderer, surface);

    SDL_FreeSurface(surface);

    // If the user has specifically declared the size of the font, use the declared size. Else, use default text font.
    // Declared size being greater than 0 is how we determine if the size was declared. m_vSize is 0 by default.
    if (m_vSize.m_X > 0 && m_vSize.m_Y > 0)
    {
        m_BaseRectangle.w = m_vSize.m_X;
        m_BaseRectangle.h = m_vSize.m_Y;
    }
    else
    {
        SDL_Point textureSize;
        SDL_QueryTexture(m_MessageTexture, NULL, NULL, &textureSize.x, &textureSize.y);
        m_BaseRectangle.w = textureSize.x;
        m_BaseRectangle.h = textureSize.y;
    }
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
    UIBase::SetColor(color);

    CreateWordTexture();
}

}