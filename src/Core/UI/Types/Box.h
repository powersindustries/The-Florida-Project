#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "../UICore.h"

namespace UI
{
class Box : public UIBase
{
public:
    Box();
    ~Box();

    void Draw(SDL_Renderer* renderer);
    void SetStyle(uint32_t uiStyleID);

    void SetSize(int width, int height);

private:

    void SetPositionNoRefresh(const int x, const int y);


};
}