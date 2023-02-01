#include "PauseScreen.h"
#include "GameGlobals.h"
#include "Game/Managers/UIManager.h"
#include "Core/Managers/SettingsManager.h"
#include "../Managers/GameManager.h"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
PauseScreen::PauseScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
PauseScreen::~PauseScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::Update()
{
    m_ReturnToGameButton.Update(CoreManagers::g_InputManager);
    m_QuitGameButton.Update(CoreManagers::g_InputManager);
    m_ControlsButton.Update(CoreManagers::g_InputManager);

    if (m_ReturnToGameButton.LeftClickPressed())
    {
        g_GameManager.SetGameIsPaused(false);
        g_UIManager.ActivatePauseMenu();
    }

    if (m_QuitGameButton.LeftClickPressed())
    {
        g_GameManager.SetGameRunning(false);
    }

    if (m_ControlsButton.LeftClickPressed())
    {
        g_UIManager.ActivateControlsScreen();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::Draw(SDL_Renderer* renderer)
{
    m_OpacityBox.Draw(renderer);
    m_BackgroundBox.Draw(renderer);
    m_Title.Draw(renderer);
    m_StackPanel.Draw(renderer);
}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::Initialize()
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

    m_Title.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_Title.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_Title.SetOffset(0, CoreManagers::g_SettingsManager.GetRelativeScreenY(75));
    m_Title.SetText("Pause Menu");
    m_Title.SetColor(g_GameGlobals.COLOR_BLACK);

    m_ReturnToGameButton.SetText("RETURN TO GAME");
    m_ReturnToGameButton.SetSize(300,50);

    m_QuitGameButton.SetText("QUIT GAME");
    m_QuitGameButton.SetSize(300,50);

    m_ControlsButton.SetText("CONTROLS");
    m_ControlsButton.SetSize(300,50);

    m_StackPanel.SetAnchor(HorizontalAlignment::eCenter,VerticalAlignment::eBottom);
    m_StackPanel.SetElementAlignment(HorizontalAlignment::eCenter,VerticalAlignment::eCenter);
    m_StackPanel.AddChild(&m_ReturnToGameButton);
    m_StackPanel.AddChild(&m_ControlsButton);
    m_StackPanel.AddChild(&m_QuitGameButton);
    m_StackPanel.SetPadding(25);

}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::OnShow()
{
}

}