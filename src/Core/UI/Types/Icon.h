#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "../UICore.h"

namespace UI
{
class Icon : public UIBase
{
public:
    Icon();
    ~Icon();

    void Draw(SDL_Renderer* renderer) override;
    void SetStyle(uint32_t uiStyleID) override;

    void SetSize(int width, int height);
    void SetTexture(const uint32_t uiTextureID);


private:

    void SetPositionNoRefresh(const int x, const int y) override;


private:

    SDL_Texture* m_Texture;

};
}