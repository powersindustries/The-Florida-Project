#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/TextBlock.h"
#include "Core/UI/Types/Button.h"
#include "Core/UI/Types/VerticalStack.h"


using namespace UI;

namespace Florida
{
class DebugScreen : public UIScreenBase
{
public:
    DebugScreen();
    ~DebugScreen();

    void Update();
    void Draw(SDL_Renderer* renderer);
    void Initialize();
    void OnShow();


private:

    void OnDamageButton();
    void OnHealButton();

    void OnIncreaseScrapButton();
    void OnIncreaseWoodButton();
    void OnIncreaseWaterButton();
    void OnIncreaseTimeButton();


private:

    Box m_BackgroundBox;
    
    VerticalStack m_MainStack;

    Button m_DamageButton;
    Button m_HealButton;
    
    Button m_IncreaseTimeButton;

    Button m_ScrapButton;
    Button m_WoodButton;
    Button m_WaterButton;

};
}