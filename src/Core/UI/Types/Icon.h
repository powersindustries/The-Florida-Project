#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "../UICoreTypes.h"

namespace CoreUI
{
class Icon : public UIBase
{
public:
    Icon();
    ~Icon();

    void Draw(SDL_Renderer* renderer);
    void SetStyle(uint32_t uiStyleID);

    void SetSize(int width, int height);
    void SetTexture(const uint32_t uiTextureID);


private:

    void SetPositionNoRefresh(const int x, const int y);


private:

    SDL_Texture* m_Texture;

};
}