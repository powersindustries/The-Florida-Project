#include "UICoreTypes.h"


namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
UIBase::UIBase()
{
    m_BaseRectangle.x = 0;
    m_BaseRectangle.y = 0;
    m_BaseRectangle.w = 100;
    m_BaseRectangle.h = 100;

    m_AnchorType = AlignmentType::eAnchored;

    m_Anchor.m_Horizontal = HorizontalAlignment::eLeft;
    m_Anchor.m_Vertical = VerticalAlignment::eTop;

    m_ElementAlignment.m_Horizontal = HorizontalAlignment::eLeft;
    m_ElementAlignment.m_Vertical = VerticalAlignment::eTop;

    m_DisplayType = DisplayType::eVisible;

    m_vOffset.m_iX = 0;
    m_vOffset.m_iY = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
UIBase::~UIBase()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIBase::SetAnchor(HorizontalAlignment horizontal, VerticalAlignment vertical)
{
    m_AnchorType = AlignmentType::eAnchored;

    m_Anchor.m_Horizontal = horizontal;
    m_Anchor.m_Vertical = vertical;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIBase::SetElementAlignment(HorizontalAlignment horizontal, VerticalAlignment vertical)
{
    m_AnchorType = AlignmentType::eAnchored;

    m_ElementAlignment.m_Horizontal = horizontal;
    m_ElementAlignment.m_Vertical = vertical;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIBase::SetOffset(int xOffset, int yOffset)
{
    m_vOffset.m_iX = xOffset;
    m_vOffset.m_iY = yOffset;

    RefreshUI();
}

}