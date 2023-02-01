#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "../Math/VectorMethods.h"

namespace CoreUI
{


enum class HorizontalAlignment
{
    eLeft,
    eCenter,
    eRight
};


enum class VerticalAlignment
{
    eTop,
    eCenter,
    eBottom
};


enum class AlignmentType
{
    eAnchored,
    ePoint
};


enum class DisplayType
{
    eVisible,
    eHidden,
    eDisabled
};


class AlignmentData
{
public:
    HorizontalAlignment m_Horizontal;
    VerticalAlignment   m_Vertical;

    // Default all anchors to be top left corner
    AlignmentData()
    {
        m_Horizontal  = HorizontalAlignment::eLeft;
        m_Vertical    = VerticalAlignment::eTop;
    }

    AlignmentData(HorizontalAlignment horizontal, VerticalAlignment vertical)
    {
        m_Horizontal = horizontal;
        m_Vertical   = vertical;
    }

    ~AlignmentData() {}
};


class UIScreenBase
{
    virtual void Update() = 0;
    virtual void Draw(SDL_Renderer* renderer) = 0;
    virtual void Initialize() = 0;
    virtual void OnShow() = 0;
};


class UIBase
{
public:
    UIBase();
    ~UIBase();

    virtual void Update() = 0;
    virtual void Draw(SDL_Renderer* renderer) = 0;
    virtual void SetPosition(int x, int y) = 0;
    virtual void RefreshUI() = 0;


    void SetAnchor(HorizontalAlignment horizontal, VerticalAlignment vertical);
    void SetElementAlignment(HorizontalAlignment horizontal, VerticalAlignment vertical);
    void SetOffset(int xOffset, int yOffset);
    
    inline DisplayType GetDisplayType() { return m_DisplayType; }
    inline void SetDisplayType(DisplayType displayType) { m_DisplayType = displayType; }

    inline int GetWidth() const  { return m_BaseRectangle.w; }
    inline int GetHeight() const { return m_BaseRectangle.h; }

    inline int GetPositionX() const { return m_BaseRectangle.x; }
    inline int GetPositionY() const { return m_BaseRectangle.y; }


    // Anchor point (x,y) relative to entire screen.
    AlignmentType m_AnchorType;

    // Anchor point (x,y) relative to entire screen.
    AlignmentData m_Anchor;

    // How the UI elements are aligned around it's position.
    AlignmentData m_ElementAlignment;

    // Offset position based on the anchor point.
    CoreMath::Vec2i m_vOffset;

    // Rectangle for determining position and size of UI element.
    SDL_Rect m_BaseRectangle;

    // Rectangle for determining position and size of UI element.
    DisplayType m_DisplayType;

};

}