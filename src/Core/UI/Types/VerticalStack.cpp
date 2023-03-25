#include "VerticalStack.h"
#include "Core/Managers/SettingsManager.h"

namespace CoreUI
{


// -------------------------------------------------------
// -------------------------------------------------------
VerticalStack::VerticalStack()
{
    m_BaseRectangle.x = 0;
    m_BaseRectangle.y = 0;
    m_BaseRectangle.w = 0;
    m_BaseRectangle.h = 0;

    m_iPadding = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
VerticalStack::~VerticalStack()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void VerticalStack::Draw(SDL_Renderer* renderer)
{
    const uint8_t uiChildCount = static_cast<uint8_t>(m_Children.size());
    for (uint8_t x = 0; x < uiChildCount; ++x)
    {
        m_Children[x]->Draw(renderer);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void VerticalStack::SetStyle(uint32_t uiStyleID)
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void VerticalStack::SetOffset(int xOffset, int yOffset)
{
	UIBase::SetOffset(xOffset, yOffset);

	RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void VerticalStack::RefreshUI()
{
    // Refresh VerticalStack's UI first.
    UIBase::RefreshUI();

	// Reset base rectangle's Width and Height.
	m_BaseRectangle.w = 0;
	m_BaseRectangle.h = 0;

    // Set original anchor points of children.
	const uint8_t uiChildCount = static_cast<uint8_t>(m_Children.size());
	for (uint8_t x = 0; x < uiChildCount; ++x)
	{
		m_Children[x]->SetAnchor(m_Anchor);
	}

	// Set the offset position of each child.
	// Set the VerticalStack's width and height as well.
	for (int x = 0; x < uiChildCount; ++x)
	{
		UIBase* currChild = m_Children[x];

		// Set the position of current child.
		currChild->SetPositionNoRefresh(m_BaseRectangle.x, (m_BaseRectangle.y + m_BaseRectangle.h));

		// Update the width and height of stack.
		const int iCurrChildWidth = currChild->GetWidth();
		if (iCurrChildWidth > m_BaseRectangle.w)
		{
			m_BaseRectangle.w = iCurrChildWidth;
		}

		m_BaseRectangle.h += currChild->GetHeight() + m_iPadding;
	}
}


// -------------------------------------------------------
// -------------------------------------------------------
void VerticalStack::AddChild(UIBase* child)
{
	m_Children.push_back(child);

	RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void VerticalStack::SetVisibility(UIVisibility visibility)
{
	UIBase::SetVisibility(visibility);

    const uint8_t uiChildCount = static_cast<uint8_t>(m_Children.size());
    for (uint8_t x = 0; x < uiChildCount; ++x)
    {
        m_Children[x]->SetVisibility(m_Visibility);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void VerticalStack::SetPadding(int padding)
{
    m_iPadding = padding;

    RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void VerticalStack::SetPositionNoRefresh(const int x, const int y)
{
	m_BaseRectangle.x = x;
	m_BaseRectangle.y = y;
}


// -------------------------------------------------------
// -------------------------------------------------------
void VerticalStack::ClearChildren()
{
    m_Children.clear();
}

}