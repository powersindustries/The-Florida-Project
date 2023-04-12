#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/UIScreenBase.h"
#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/TextBlock.h"
#include "Core/UI/Types/Button.h"
#include "Core/UI/Types/VerticalStack.h"

using namespace UI;

namespace Florida
{
class PauseScreen : public UIScreenBase
{
public:
    PauseScreen();
    ~PauseScreen();

    void Initialize();

    void Update();
    void Draw(SDL_Renderer* renderer);

    void OnShow();
    void RemoveSelf();


private:
    
    VerticalStack m_VerticalStack;

    Box m_OpacityBox;
    Box m_BackgroundBox;
    TextBlock m_Title;

    Button m_ReturnToGameButton;
    Button m_QuitGameButton;
    Button m_ControlsButton;

};
}