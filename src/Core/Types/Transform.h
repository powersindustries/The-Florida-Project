#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

namespace CoreTypes
{

class Transform
{
public:
    Transform();
    ~Transform();

    void SetTransform(SDL_Rect& rectangle, int s = 1);
    void SetTransform(int x, int y, int w, int h, int s = 1);

    void SetPosition(int x, int y);
    void SetPosition(SDL_Rect& rectangle);


public:

    int m_iPositionX;
    int m_iPositionY;

    int m_iWidth;
    int m_iHeight;
    int m_iScale;

};

}