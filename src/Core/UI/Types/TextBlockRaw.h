#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>

#include "../UICore.h"

namespace UI
{
class TextBlockRaw : public UIBase
{
public:
    TextBlockRaw();
    ~TextBlockRaw();

    void Draw(SDL_Renderer* renderer) override;
    void SetStyle(uint32_t uiStyleID) override;

    void SetFont(uint32_t fontIDHash);
    void SetColor(SDL_Color color) override;
    void SetText(std::string text);
    void SetVisibility(UIVisibility visibility) override;
    void SetSize(const int x, const int y);
    void SetWordWrap(uint8_t uiWordWrap);

    void SetPosition(const int x, const int y);


private:

    void SetPositionNoRefresh(const int x, const int y) override;

    void CreateWordTexture();


private:

    std::string m_Text;

    SDL_Texture* m_MessageTexture;
    TTF_Font* m_Font;

    Core::Vec2i m_vSize;

    uint8_t m_uiWordWrap;

};
}