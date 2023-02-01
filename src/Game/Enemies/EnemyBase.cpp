#include "EnemyBase.h"


namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
EnemyBase::EnemyBase() 
    : m_Sprite(nullptr)
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
EnemyBase::~EnemyBase()
{
    delete m_Sprite;
}

}
