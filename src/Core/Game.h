#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <SDL_mixer.h> // SDL Sound

namespace Florida
{
class Game
{
public:

    Game();
    ~Game();

    void InitializeSession();
    void EndSession();

    void ProcessInputs();

    void Update();
    void Draw();


public:

    SDL_Window* m_Window;

    static SDL_Renderer* m_Renderer;


private:

    float m_fDeltaTime;
    uint32_t m_uiTicksLastFrame;

};
}