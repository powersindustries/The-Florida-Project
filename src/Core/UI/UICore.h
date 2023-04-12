#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "../Utility/VectorMethods.h"


namespace UI
{


enum class Anchor
{
    eTopLeft,
    eTopCenter,
    eTopRight,
    eCenterLeft,
    eCenter,
    eCenterRight,
    eBottomLeft,
    eBottomCenter,
    eBottomRight
};


enum class UIVisibility
{
    eVisible,
    eHidden,
    eDisabled
};


enum MouseState
{
    eHover  = 1 << 0, // Mouse Hover
    eLMouse = 1 << 1, // Left Mouse
    eRMouse = 1 << 2  // Right Mouse
};


class UIBase
{
public:
    UIBase();
    ~UIBase();

    virtual void Draw(SDL_Renderer* renderer) = 0;
    virtual void SetStyle(uint32_t uiStyleID) = 0;

    void Update();
    void RefreshUI();

    void SetAnchor(Anchor anchor);
    void SetAlignment(Anchor alignment);
    void SetOffset(const int x, const int y);
    
    inline void SetVisibility(UIVisibility displayType) { m_Visibility = displayType; }
    inline UIVisibility GetVisibility() { return m_Visibility; }
    inline bool IsVisible() { return m_Visibility != UIVisibility::eHidden; }
    inline bool IsDisabled() { return m_Visibility == UIVisibility::eDisabled; }

    inline int GetWidth() const  { return m_BaseRectangle.w; }
    inline int GetHeight() const { return m_BaseRectangle.h; }

    inline bool MouseHovered() const { return m_uiMouseState & MouseState::eHover; };
    inline bool LeftClickPressed() const { return m_uiMouseState & MouseState::eLMouse; };
    inline bool RightClickPressed() const { return m_uiMouseState & MouseState::eRMouse; };

    inline void SetColor(SDL_Color color) { m_Color = color; }

    TTF_Font* GetDefaultFont();


protected:

    virtual void SetPositionNoRefresh(const int x, const int y) = 0;


public:

    // Dictates which part of the screen the UI is attached to.
    // Defaults value: X=0, Y=0, W=100, H=100
    SDL_Rect m_BaseRectangle;


    // Dictates which part of the screen the UI is attached to.
    // Defaults value: Anchor::eTopLeft
    Core::Vec2i m_vOffset;


    // Dictates which part of the screen the UI is attached to.
    // Defaults value: Anchor::eTopLeft
    Anchor m_Anchor;


    // How should the UI element hang off of the anchor point.
    // Defaults value: Anchor::eTopLeft
    Anchor m_Alignment;


    // Dictates how a UI primitive should be drawn.
    // Defaults value: UIVisibility::eVisible
    UIVisibility m_Visibility;


    // State of the mouse interacting with the UI element.
    // Defaults value: 0
    uint8_t m_uiMouseState;


    // State of the mouse interacting with the UI element.
    // Defaults value: 0
    SDL_Color m_Color;


protected:

    bool m_bStyleSet;


    friend class VerticalStack;
    friend class HorizontalStack;

};

}