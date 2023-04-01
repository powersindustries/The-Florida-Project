#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>

#include "../UICoreTypes.h"

namespace UI
{
class TextBlock : public UIBase
{
public:
    TextBlock();
    ~TextBlock();

    void Draw(SDL_Renderer* renderer);
    void SetStyle(uint32_t uiStyleID);

    void SetFont(uint32_t fontIDHash);
    void SetColor(SDL_Color color);
    void SetText(std::string text);
    void SetVisibility(UIVisibility visibility);
    void SetSize(const int x, const int y);
    void SetWordWrap(uint8_t uiWordWrap);


private:

    void SetPositionNoRefresh(const int x, const int y);

    void CreateWordTexture();


private:

    std::string m_Text;

    SDL_Texture* m_MessageTexture;
    TTF_Font* m_Font;

    Core::Vec2i m_vSize;

    uint8_t m_uiWordWrap;

};
}