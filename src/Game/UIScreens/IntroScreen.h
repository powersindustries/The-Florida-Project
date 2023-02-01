#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/Button.h"
#include "Core/UI/Types/StackPanel.h"
#include "Core/UI/Types/Icon.h"

using namespace CoreUI;

namespace Florida
{
class IntroScreen : public UIScreenBase
{
public:
    IntroScreen();
    ~IntroScreen();

    void Update();
    void Draw(SDL_Renderer* renderer);
    void Initialize();
    void OnShow();


private:

    Box m_OpacityBox;
    Box m_BackgroundBox;

    Icon m_GameLogo;

    Button m_StartGameButton;
    Button m_ControlsButton;
    Button m_ExitGameButton;

    StackPanel m_StackPanel;

};
}