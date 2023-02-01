#include "IntroScreen.h"
#include "GameGlobals.h"
#include "Core/Managers/SettingsManager.h"
#include "../Managers/GameManager.h"
#include "../Managers/UIManager.h"
#include "Core/Systems/Hash.h"

#define FLORIDALOGO_ID "txt_FloridaProjectLogo"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
IntroScreen::IntroScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
IntroScreen::~IntroScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void IntroScreen::Update()
{
    m_StartGameButton.Update(CoreManagers::g_InputManager);
    m_ControlsButton.Update(CoreManagers::g_InputManager);
    m_ExitGameButton.Update(CoreManagers::g_InputManager);

    if (m_StartGameButton.LeftClickPressed())
    {
        g_GameManager.SetIntroScreen(true);
        g_GameManager.StartNewGame();
    }
    
    if (m_ControlsButton.LeftClickPressed())
    {
        g_UIManager.ActivateControlsScreen();
    }

    if (m_ExitGameButton.LeftClickPressed())
    {
        g_GameManager.SetGameRunning(false);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void IntroScreen::Draw(SDL_Renderer* renderer)
{
    m_OpacityBox.Draw(renderer);
    m_BackgroundBox.Draw(renderer);
    m_GameLogo.Draw(renderer);

    m_StackPanel.Draw(renderer);

}


// -------------------------------------------------------
// -------------------------------------------------------
void IntroScreen::Initialize()
{
    m_OpacityBox.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_OpacityBox.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_OpacityBox.SetSize(CoreManagers::g_SettingsManager.GetScreenWidth(), CoreManagers::g_SettingsManager.GetScreenHeight());
    m_OpacityBox.SetColor(g_GameGlobals.COLOR_BLACK);
    m_OpacityBox.SetDisplayType(DisplayType::eDisabled);

    m_BackgroundBox.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_BackgroundBox.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_BackgroundBox.SetSize(CoreManagers::g_SettingsManager.GetScreenWidth() / 2, CoreManagers::g_SettingsManager.GetScreenHeight() - CoreManagers::g_SettingsManager.GetRelativeScreenY(50));
    m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);


    m_GameLogo.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_GameLogo.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_GameLogo.SetOffset(0, CoreManagers::g_SettingsManager.GetRelativeScreenY(-150));
    m_GameLogo.SetSize(500,300);
    m_GameLogo.SetTexture(CoreSystems::StringToHash32(std::string(FLORIDALOGO_ID)));

    m_StartGameButton.SetText("START NEW GAME");
    m_StartGameButton.SetSize(300, 50);

    m_ControlsButton.SetText("CONTROLS");
    m_ControlsButton.SetSize(300, 50);

    m_ExitGameButton.SetText("EXIT GAME");
    m_ExitGameButton.SetSize(300, 50);


    m_StackPanel.SetAnchor(HorizontalAlignment::eCenter,VerticalAlignment::eBottom);
    m_StackPanel.SetElementAlignment(HorizontalAlignment::eCenter,VerticalAlignment::eTop);
    m_StackPanel.AddChild(&m_StartGameButton);
    m_StackPanel.AddChild(&m_ControlsButton);
    m_StackPanel.AddChild(&m_ExitGameButton);
    m_StackPanel.SetPadding(25);
    m_StackPanel.SetOffset(0,50);

}


// -------------------------------------------------------
// -------------------------------------------------------
void IntroScreen::OnShow()
{
}

}