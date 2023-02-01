#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "../UICoreTypes.h"
#include "Core/Types/Sprite.h"

namespace CoreUI
{

class Icon : public UIBase
{
public:
    Icon();
    ~Icon();

    Icon(uint32_t uiTextureID);

    void Update();
    void Draw(SDL_Renderer* renderer);
    void SetPosition(int x, int y);
    void RefreshUI();

    void SetSize(int width, int height);

    void SetTexture(uint32_t uiTextureID);


    inline void SetColor(SDL_Color color) { m_Color = color; }


private:

    SDL_Color m_Color;

    CoreTypes::Sprite* m_Sprite;

};

}