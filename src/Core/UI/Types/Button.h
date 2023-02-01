#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>

#include "../UICoreTypes.h"
#include "Core/Managers/InputManager.h"

enum ButtonStates
{
    eHover  = 1 << 0, // Mouse Hover
    eLMouse = 1 << 1, // Left Mouse
    eRMouse = 1 << 2 // Right Mouse
};

namespace CoreUI
{

class Button : public UIBase
{
public:
    Button();
    ~Button();

    void Update();
    void Update(CoreManagers::InputManager& inputManager);
    void Draw(SDL_Renderer* renderer);
    void SetPosition(int x, int y);
    void RefreshUI();

    void SetFont(uint32_t fontIDHash);

    void SetSize(int width, int height);
    void SetText(std::string text);
    void SetTextAlignment(HorizontalAlignment alignment);

    inline void SetBaseColor(SDL_Color color) { m_BaseColor = color; };
    inline void SetHoverColor(SDL_Color color) { m_HoverColor = color; };

    inline bool MouseHovered() const { return m_uiButtonStateFlags & ButtonStates::eHover; };
    inline bool LeftClickPressed() const { return m_uiButtonStateFlags & ButtonStates::eLMouse; };
    inline bool RightClickPressed() const { return m_uiButtonStateFlags & ButtonStates::eRMouse; };

    inline uint32_t GetData1() const { return m_iData1; };
    inline uint32_t GetData2() const { return m_iData2; };
    inline void SetData1(uint32_t uiData) { m_iData1 = uiData; };
    inline void SetData2(uint32_t uiData) { m_iData2 = uiData; };


private:
 
    bool MouseCollisionDetected(int mouseX, int mouseY);
    void RefreshInternalUI();


private:

    // SDL Types
    SDL_Texture* m_MessageTexture;
    TTF_Font* m_Font;

    SDL_Rect m_FontRectangle;

    // Button States
    uint8_t m_uiButtonStateFlags;

    // Button Properties
    std::string m_Text;
    HorizontalAlignment m_TextAlignment;

    SDL_Color m_BaseColor;
    SDL_Color m_HoverColor;

    // Data Attached to Button
    int32_t m_iData1;
    int32_t m_iData2;

};

}