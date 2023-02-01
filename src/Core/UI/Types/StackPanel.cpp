#include "StackPanel.h"
#include "Core/Managers/SettingsManager.h"

namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
StackPanel::StackPanel()
{
    m_iPadding = 0;

    m_Alignment = StackpanelAlignment::eVertical;
}


// -------------------------------------------------------
// -------------------------------------------------------
StackPanel::~StackPanel()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::Update()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::Draw(SDL_Renderer* renderer)
{
    const uint8_t childCount = static_cast<uint8_t>(m_Children.size());
    for (uint8_t x = 0; x < childCount; ++x)
    {
        m_Children[x]->Draw(renderer);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::SetPosition(int x, int y)
{
    m_AnchorType = AlignmentType::ePoint;

    m_BaseRectangle.x = x;
    m_BaseRectangle.y = y;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::RefreshUI()
{
    // Set Anchor position.
    int iCenterX = CoreManagers::g_SettingsManager.GetScreenWidth() / 2;
    int iRightX  = CoreManagers::g_SettingsManager.GetScreenWidth();

    int iCenterY = CoreManagers::g_SettingsManager.GetScreenHeight() / 2;
    int iBottomY = CoreManagers::g_SettingsManager.GetScreenHeight();

    // If not unique, set m_BaseRectangle position to be an anchor point.
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
            m_BaseRectangle.x = iCenterX + m_vOffset.m_iX;
            break;
        }
        case HorizontalAlignment::eRight:
        {
            m_BaseRectangle.x = iRightX - m_vOffset.m_iX;
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
            m_BaseRectangle.y = iCenterY + m_vOffset.m_iY;
            break;
        }
        case VerticalAlignment::eBottom:
        {
            m_BaseRectangle.y = iBottomY - m_vOffset.m_iY;
            break;
        }
        default:
            break;
        }
    }


    const uint8_t uiChildCount = static_cast<uint8_t>(m_Children.size());

    // Get the width and height values for the stack.
    int iStackWidth  = 0;
    int iStackHeight = 0;
    for (int x = 0; x < uiChildCount; ++x)
    {
        UIBase* currentChild = m_Children[x];
        if (m_Alignment == StackpanelAlignment::eVertical)
        {
            if (currentChild->GetWidth() > iStackWidth)
            {
                iStackWidth = currentChild->GetWidth();
            }

            iStackHeight += currentChild->GetHeight() + m_iPadding;
        }
        else
        {
            iStackWidth += currentChild->GetWidth() + m_iPadding;

            if (currentChild->GetHeight() > iStackHeight)
            {
                iStackHeight = currentChild->GetHeight();
            }
        }
    }

    // Offset m_BaseRectangle position based on m_ElementAlignment.
    switch (m_ElementAlignment.m_Horizontal)
    {
    case HorizontalAlignment::eLeft: 
    {
        break;
    }
    case HorizontalAlignment::eCenter: 
    {
        m_BaseRectangle.x = m_BaseRectangle.x - (iStackWidth / 2);
        break;
    }
    case HorizontalAlignment::eRight: 
    {
        m_BaseRectangle.x = m_BaseRectangle.x - (iStackWidth / 2);
        break;
    }
    default: 
    {
        break;
    }
    }

    switch (m_ElementAlignment.m_Vertical)
    {
    case VerticalAlignment::eTop: 
    {
        break;
    }
    case VerticalAlignment::eCenter: 
    {
        m_BaseRectangle.y = m_BaseRectangle.y - (iStackHeight / 4);
        break;
    }
    case VerticalAlignment::eBottom: 
    {
        m_BaseRectangle.y = m_BaseRectangle.y - (iStackHeight / 2);
        break;
    }
    default: 
    {
        break;
    }
    }

    // Set children positions.
    for (int x = 0; x < uiChildCount; ++x)
    {
        UIBase* currentChild = m_Children[x];

        if (x == 0)
        {
            if (m_Anchor.m_Horizontal == HorizontalAlignment::eRight && m_Anchor.m_Vertical == VerticalAlignment::eTop)
            {
                currentChild->SetPosition(m_BaseRectangle.x - iStackWidth, m_BaseRectangle.y);
            }
            else if (m_Alignment == StackpanelAlignment::eVertical   && m_Anchor.m_Horizontal == HorizontalAlignment::eRight || 
                     m_Alignment == StackpanelAlignment::eHorizontal && m_Anchor.m_Horizontal == HorizontalAlignment::eRight)
            {
                currentChild->SetPosition(m_BaseRectangle.x - iStackWidth, m_BaseRectangle.y - iStackHeight);
            }
            else
            {
                currentChild->SetPosition(m_BaseRectangle.x, m_BaseRectangle.y - iStackHeight);
            }
        }
        else
        {
            UIBase* prevChild = m_Children[x - 1];
            int iCurrChildY = prevChild->GetPositionY() + prevChild->GetHeight() + m_iPadding;
            int iCurrChildX = prevChild->GetPositionX() + prevChild->GetWidth()  + m_iPadding;
            if (m_Alignment == StackpanelAlignment::eVertical && m_Anchor.m_Horizontal == HorizontalAlignment::eRight)
            {
                currentChild->SetPosition(m_BaseRectangle.x - iStackWidth, iCurrChildY);
            }
            else if (m_Alignment == StackpanelAlignment::eVertical)
            {
                currentChild->SetPosition(m_BaseRectangle.x, iCurrChildY);
            }
            else
            {
                currentChild->SetPosition(iCurrChildX, m_BaseRectangle.y - iStackHeight);
            }
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::SetDisplayType(DisplayType displayType)
{
    const uint8_t childCount = static_cast<uint8_t>(m_Children.size());
    for (uint8_t x = 0; x < childCount; ++x)
    {
        m_Children[x]->SetDisplayType(displayType);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::AddChild(UIBase* child)
{
    m_Children.push_back(child);

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::SetChildAlignment(StackpanelAlignment alignment)
{
    m_Alignment = alignment;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::SetPadding(int padding)
{
    m_iPadding = padding;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void StackPanel::ClearChildren()
{
    m_Children.clear();
}

}