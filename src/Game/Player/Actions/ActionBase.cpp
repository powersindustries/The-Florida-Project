#include "ActionBase.h"
#include "Core/Utility/Utility.h"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
ActionBase::ActionBase()
{
    m_BaseRectangle.x = 0;
    m_BaseRectangle.y = 0;
    m_BaseRectangle.w = 0;
    m_BaseRectangle.h = 0;

    m_Direction = Direction::eRight;

    m_bActive = true;
}


// -------------------------------------------------------
// -------------------------------------------------------
ActionBase::~ActionBase()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
bool ActionBase::CollidedWithEnemy(const SDL_Rect& rect1, const SDL_Rect& rect2)
{
    return Core::Utility::CollisionBetweenTwoRectangles(rect1, rect2);
}

}
