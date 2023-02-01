#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#define __PROJECT_DIRECTORY__ PROJECT_PATH

namespace Florida
{


// -------------------------------------------------------
// Enum for dictating cardinal directions.
// -------------------------------------------------------
enum class Direction
{
    eUp,
    eDown,
    eLeft,
    eRight
};


// -------------------------------------------------------
// Class that holds all global data for game.
// -------------------------------------------------------
class GameGlobals
{
public:

    const int BASE_WINDOW_SCALE_WIDTH  = 1920;
    const int BASE_WINDOW_SCALE_HEIGHT = 1080;

    const int FPS = 60;
    const int FRAME_TARGET_TIME = 1000 / FPS;

    const double PI = 3.14159265;

    const uint8_t ITEM_ANIMATION_SPEED = 180;

    // Colors
    const SDL_Color COLOR_BLACK   = { 0  , 0 ,  0, 255 };
    const SDL_Color COLOR_WHITE   = { 255, 255, 255, 255 };
    const SDL_Color COLOR_BLUE    = { 0  , 0  , 255, 255 };
    const SDL_Color COLOR_GREEN   = { 0  , 128, 0, 255 };
    const SDL_Color COLOR_NAVY    = { 0  , 0  , 128, 255 };
    const SDL_Color COLOR_TEAL    = { 0  , 128, 128, 255 };
    const SDL_Color COLOR_LIME    = { 0  , 255, 0, 255 };
    const SDL_Color COLOR_AQUA    = { 0  , 255, 255, 255 };
    const SDL_Color COLOR_MAROON  = { 128, 0  , 0, 255 };
    const SDL_Color COLOR_PURPLE  = { 128, 0  , 128, 255 };
    const SDL_Color COLOR_OLIVE   = { 128, 128, 0, 255 };
    const SDL_Color COLOR_GRAY    = { 128, 128, 128, 255 };
    const SDL_Color COLOR_SILVER  = { 192, 192, 192, 255 };
    const SDL_Color COLOR_RED     = { 255, 0  , 0, 255 };
    const SDL_Color COLOR_FUCHSIA = { 255, 0  , 255, 255 };
    const SDL_Color COLOR_YELLOW  = { 255, 255, 0, 255 };

};

extern GameGlobals g_GameGlobals;
}