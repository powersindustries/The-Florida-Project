#include "Transform.h"

namespace Core
{


// -------------------------------------------------------
// -------------------------------------------------------
Transform::Transform()
{
    m_iPositionX = 0;
    m_iPositionY = 0;
    m_iWidth     = 0;
    m_iHeight    = 0;
    m_iScale     = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
Transform::~Transform()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void Transform::SetTransform(SDL_Rect& rectangle, int s /*= 1*/)
{
    m_iPositionX = rectangle.x;
    m_iPositionY = rectangle.y;
    m_iWidth     = rectangle.w;
    m_iHeight    = rectangle.h;
    m_iScale     = s;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Transform::SetTransform(int x, int y, int w, int h, int s /*= 1*/)
{
    m_iPositionX = x;
    m_iPositionY = y;
    m_iWidth     = w;
    m_iHeight    = h;
    m_iScale     = s;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Transform::SetPosition(int x, int y)
{
    m_iPositionX = x;
    m_iPositionY = y;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Transform::SetPosition(SDL_Rect& rectangle)
{
    m_iPositionX = rectangle.x;
    m_iPositionY = rectangle.y;
}


}