#include "Button.h"
#include "GameGlobals.h"
#include "Core/Game.h"
#include "Core/Systems/Systems.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/Managers/StyleManager.h"
#include "Game/Managers/AssetManager.h"

namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
Button::Button()
    : m_Font(nullptr), m_MessageTexture(nullptr)
{
    m_TextRectangle.x = 0;
    m_TextRectangle.y = 0;
    m_TextRectangle.w = 100;
    m_TextRectangle.h = 100;

    m_BaseColor = Florida::g_GameGlobals.COLOR_BLACK;
    m_HoverColor = Florida::g_GameGlobals.COLOR_GRAY;
    m_PressedColor = Florida::g_GameGlobals.COLOR_WHITE;
    m_TextColor = Florida::g_GameGlobals.COLOR_WHITE;

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
void Button::Draw(SDL_Renderer* renderer)
{
    if (m_Visibility == UIVisibility::eHidden)
    {
        return;
    }

    if (MouseHovered())
    {
        if (LeftClickPressed() || RightClickPressed())
        {
            SDL_SetRenderDrawColor(renderer,
                m_PressedColor.r,
                m_PressedColor.g,
                m_PressedColor.b,
                m_PressedColor.a);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer,
                m_HoverColor.r,
                m_HoverColor.g,
                m_HoverColor.b,
                m_HoverColor.a);
        }
    }
    else
    {
        SDL_SetRenderDrawColor(renderer,
            m_BaseColor.r,
            m_BaseColor.g,
            m_BaseColor.b,
            m_Visibility == UIVisibility::eVisible ? m_BaseColor.a : (m_BaseColor.a / 2) );
    }

    SDL_RenderFillRect(renderer, &m_BaseRectangle);
    SDL_RenderCopy(renderer, m_MessageTexture, NULL, &m_TextRectangle);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetStyle(uint32_t uiStyleID)
{
    const CoreManagers::ButtonStyle& currStyleData = CoreManagers::g_StyleManager.GetButtonStyle(uiStyleID);

    m_Font = Florida::g_AssetManager.m_FontAssets[currStyleData.m_uiFont].m_Font;

    m_BaseColor = currStyleData.m_BaseColor;
    m_HoverColor = currStyleData.m_HoverColor;
    m_PressedColor = currStyleData.m_PressedColor;
    m_TextColor = currStyleData.m_TextColor;

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
void Button::SetText(std::string text)
{
    m_Text = text;

    CreateWordTexture();
    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::RefreshUI()
{
    UIBase::RefreshUI();

	UpdateTextPositionInternal();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetOffset(const int x, const int y)
{
    UIBase::SetOffset(x, y);

	UpdateTextPositionInternal();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetSize(const int x, const int y)
{
    m_BaseRectangle.w = x;
    m_BaseRectangle.h = y;

    UpdateTextPositionInternal();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::SetPositionNoRefresh(const int x, const int y)
{
    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;

    UpdateTextPositionInternal();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::CreateWordTexture()
{
    SDL_Color tempColor =
    {
    m_TextColor.r,
    m_TextColor.g,
    m_TextColor.b,
    m_Visibility == UIVisibility::eVisible ? static_cast<Uint8>(m_TextColor.a) : static_cast<Uint8>(m_TextColor.a / 2)
    };

    SDL_Surface* surface = nullptr;
    if (m_Font)
    {
        surface = TTF_RenderText_Solid(m_Font, m_Text.c_str(), tempColor);
    }
    else
    {
        surface = TTF_RenderText_Solid(GetDefaultFont(), m_Text.c_str(), tempColor);
    }

    SDL_DestroyTexture(m_MessageTexture);
    m_MessageTexture = SDL_CreateTextureFromSurface(Florida::Game::m_Renderer, surface);

    SDL_FreeSurface(surface);

    SDL_Point textureSize;
    SDL_QueryTexture(m_MessageTexture, NULL, NULL, &textureSize.x, &textureSize.y);
    m_TextRectangle.w = textureSize.x;
    m_TextRectangle.h = textureSize.y;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Button::UpdateTextPositionInternal()
{
    m_TextRectangle.x = m_BaseRectangle.x + (m_BaseRectangle.w / 2) - (m_TextRectangle.w / 2);
    m_TextRectangle.y = m_BaseRectangle.y + (m_BaseRectangle.h / 2) - (m_TextRectangle.h / 2);
}

}