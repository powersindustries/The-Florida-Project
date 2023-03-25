#include "Box.h"
#include "GameGlobals.h"
#include "Core/Managers/SettingsManager.h"

namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
Box::Box()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
Box::~Box()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::Draw(SDL_Renderer* renderer)
{
    if (m_Visibility == UIVisibility::eHidden)
    {
        return;
    }

    SDL_SetRenderDrawColor(renderer, m_Color.r, m_Color.g, m_Color.b, m_Visibility == UIVisibility::eVisible ? m_Color.a : (m_Color.a / 2));
    SDL_RenderFillRect(renderer, &m_BaseRectangle);
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::SetStyle(uint32_t uiStyleID)
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::SetSize(int width, int height)
{
    m_BaseRectangle.w = width;
    m_BaseRectangle.h = height;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Box::SetPositionNoRefresh(const int x, const int y)
{
    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;
}

}