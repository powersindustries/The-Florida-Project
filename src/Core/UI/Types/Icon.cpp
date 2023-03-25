#include "Icon.h"
#include "GameGlobals.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/Systems/Logging.h"
#include "Game/Managers/AssetManager.h"

namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
Icon::Icon()
    : m_Texture(nullptr)
{
    m_BaseRectangle.x = 0;
    m_BaseRectangle.y = 0;
    m_BaseRectangle.w = 100;
    m_BaseRectangle.h = 100;
}


// -------------------------------------------------------
// -------------------------------------------------------
Icon::~Icon()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Icon::Draw(SDL_Renderer* renderer)
{
    if (m_Visibility == UIVisibility::eHidden)
    {
        return;
    }

    if (m_Texture)
    {
        SDL_RenderCopy(renderer, m_Texture, NULL, &m_BaseRectangle);
    }
    else
    {
        // If no Texture is present, just draw a box.
		SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b, m_Visibility == UIVisibility::eVisible ? m_Color.a : (m_Color.a / 2));
		SDL_RenderFillRect(renderer, &m_BaseRectangle);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Icon::SetStyle(uint32_t uiStyleID)
{
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
void Icon::SetTexture(const uint32_t uiTextureID)
{
	const Florida::TextureAssetData& textureAssetData = Florida::g_AssetManager.m_TextureAssets[uiTextureID];
    if (textureAssetData.m_Texture)
    {
		m_Texture = textureAssetData.m_Texture;

		m_BaseRectangle.x = 0;
		m_BaseRectangle.y = 0;
		m_BaseRectangle.w = textureAssetData.m_iWidth;
		m_BaseRectangle.h = textureAssetData.m_iHeight;

		RefreshUI();
    }
    else
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Texture Asset ID does not exist!");
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Icon::SetPositionNoRefresh(const int x, const int y)
{
    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;
}

}