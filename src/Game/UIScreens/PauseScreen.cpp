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
    m_ReturnToGameButton.Update();
    m_QuitGameButton.Update();
    m_ControlsButton.Update();

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
    m_VerticalStack.Draw(renderer);
}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::Initialize()
{
    m_OpacityBox.SetAnchor(Anchor::eTopLeft);
    m_OpacityBox.SetColor(g_GameGlobals.COLOR_BLACK);
    m_OpacityBox.SetSize(
        Core::g_SettingsManager.GetScreenWidth(), 
        Core::g_SettingsManager.GetScreenHeight()
    );
    m_OpacityBox.SetVisibility(UIVisibility::eDisabled);

    m_BackgroundBox.SetAnchor(Anchor::eTopCenter);
    m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);
    m_BackgroundBox.SetSize(Core::g_SettingsManager.GetScreenWidth() / 2, Core::g_SettingsManager.GetScreenHeight() - Core::g_SettingsManager.GetRelativeScreenY(50));
    m_BackgroundBox.SetOffset(
        ( (m_BackgroundBox.GetWidth() / 2) * -1),
        0
    );

    m_Title.SetAnchor(Anchor::eTopCenter);
    m_Title.SetColor(g_GameGlobals.COLOR_BLACK);
    m_Title.SetText("Pause Menu");
    m_Title.SetOffset(
        ( (m_Title.GetWidth() / 2) * -1),
        Core::g_SettingsManager.GetRelativeScreenY(75)
    );

    m_ReturnToGameButton.SetText("RETURN TO GAME");
    m_ReturnToGameButton.SetSize(300,50);

    m_QuitGameButton.SetText("QUIT GAME");
    m_QuitGameButton.SetSize(300,50);

    m_ControlsButton.SetText("CONTROLS");
    m_ControlsButton.SetSize(300,50);

    m_VerticalStack.SetAnchor(Anchor::eCenter);
    m_VerticalStack.SetPadding(50);
    m_VerticalStack.AddChild(&m_ReturnToGameButton);
    m_VerticalStack.AddChild(&m_ControlsButton);
    m_VerticalStack.AddChild(&m_QuitGameButton);
    m_VerticalStack.SetOffset(
        ( (m_VerticalStack.GetWidth() / 2) * -1),
        Core::g_SettingsManager.GetRelativeScreenY(75)
    );

}


// -------------------------------------------------------
// -------------------------------------------------------
void PauseScreen::OnShow()
{
}

}