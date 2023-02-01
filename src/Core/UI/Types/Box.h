#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "../UICoreTypes.h"

namespace CoreUI
{

class Box : public UIBase
{
public:
    Box();
    ~Box();

    void Update();
    void Draw(SDL_Renderer* renderer);
    void SetPosition(int x, int y);
    void RefreshUI();


    void SetSize(int width, int height);

    inline void SetColor(SDL_Color color) { m_Color = color; }


private:

    SDL_Color m_Color;

};
}