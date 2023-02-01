#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/TextBlock.h"
#include "Core/UI/Types/Button.h"

using namespace CoreUI;

namespace Florida
{
class GameOverScreen : public UIScreenBase
{
public:
    GameOverScreen();
    ~GameOverScreen();

    void Update();
    void Draw(SDL_Renderer* renderer);
    void Initialize();
    void OnShow();

    void SetGameOverMessage(std::string sMessage);


private:

    Box m_OpacityBox;
    Box m_BackgroundBox;
    TextBlock m_Title;

    Button m_RestartGameButton;
    TextBlock m_GameOverText;

};
}