#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/UIScreenBase.h"
#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/Button.h"
#include "Core/UI/Types/Icon.h"
#include "Core/UI/Types/VerticalStack.h"

using namespace UI;

namespace Florida
{
class IntroScreen : public UIScreenBase
{
public:
    IntroScreen();
    ~IntroScreen();

    void Initialize() override;

    void Update() override;
    void Draw(SDL_Renderer* renderer) override;

    void OnShow() override;
    void RemoveSelf() override;


private:

    Box m_OpacityBox;
    Box m_BackgroundBox;

    Icon m_GameLogo;

    Button m_StartGameButton;
    Button m_ControlsButton;
    Button m_ExitGameButton;

    VerticalStack m_VerticalStack;

};
}