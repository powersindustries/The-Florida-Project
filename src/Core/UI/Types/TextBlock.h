#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>

#include "../UICoreTypes.h"

namespace CoreUI
{

class TextBlock : public UIBase
{
public:
    TextBlock();
    ~TextBlock();

    void Update();
    void Draw(SDL_Renderer* renderer);
    void SetPosition(int x, int y);
    void RefreshUI();

    void SetSize(int width, int height);
    void SetFont(uint32_t fontIDHash);
    void SetColor(SDL_Color color);
    void SetText(std::string text);

    inline std::string GetText() const { return m_Text; };


private:

    SDL_Texture* m_MessageTexture;
    TTF_Font* m_Font;

    SDL_Color m_Color;

    std::string m_Text;

};

}