#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/UIScreenBase.h"
#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/TextBlock.h"
#include "Core/UI/Types/Button.h"

using namespace UI;

namespace Florida
{
class GameOverScreen : public UIScreenBase
{
public:
    GameOverScreen();
    ~GameOverScreen();

    void Initialize() override;

    void Update() override;
    void Draw(SDL_Renderer* renderer) override;

    void OnShow() override;
    void RemoveSelf() override;

    void SetGameOverMessage(std::string sMessage);


private:

    Box m_OpacityBox;
    Box m_BackgroundBox;
    TextBlock m_Title;

    Button m_RestartGameButton;
    TextBlock m_GameOverText;

};
}