#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>

#include "../UICore.h"
#include "Core/Managers/InputManager.h"

namespace UI
{
class Button : public UIBase
{
public:
    Button();
    ~Button();

    void Draw(SDL_Renderer* renderer);
    void SetStyle(uint32_t uiStyleID);

    void RefreshUI();

    void SetOffset(const int x, const int y);
    void SetSize(const int x, const int y);

    void SetText(std::string text);

    inline void SetBackgroundColor(SDL_Color color) { m_BaseColor = color; };
    inline void SetHoverColor(SDL_Color color) { m_HoverColor = color; };

    inline uint32_t GetData1() const { return m_iData1; };
    inline uint32_t GetData2() const { return m_iData2; };
    inline void SetData1(uint32_t uiData) { m_iData1 = uiData; };
    inline void SetData2(uint32_t uiData) { m_iData2 = uiData; };


private:

    void SetPositionNoRefresh(const int x, const int y);

    void CreateWordTexture();
    void UpdateTextPositionInternal();


private:

    TTF_Font* m_Font;
    SDL_Texture* m_MessageTexture;
    SDL_Rect m_TextRectangle;

    std::string m_Text;

    SDL_Color m_BaseColor;
    SDL_Color m_HoverColor;
    SDL_Color m_PressedColor;
    SDL_Color m_TextColor;

    int32_t m_iData1;
    int32_t m_iData2;

};
}