#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include "Core/Game.h"
#include "Game/Managers/GameManager.h"

using namespace Florida;

int main()
{
    Game* m_Game = new Game;
    m_Game->InitializeSession();


    while (g_GameManager.ApplicationIsRunning())
    {
        m_Game->ProcessInputs();
        m_Game->Update();
        m_Game->Draw();
    }

    m_Game->EndSession();
    delete m_Game;

    return 0;
}