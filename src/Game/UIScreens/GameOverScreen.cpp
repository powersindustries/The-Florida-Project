#include "GameOverScreen.h"
#include "GameGlobals.h"
#include "Core/Managers/SettingsManager.h"
#include "../Managers/GameManager.h"


namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
GameOverScreen::GameOverScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
GameOverScreen::~GameOverScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameOverScreen::Update()
{
    m_RestartGameButton.Update(CoreManagers::g_InputManager);

    if (m_RestartGameButton.LeftClickPressed())
    {
        g_GameManager.StartNewGame();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameOverScreen::Draw(SDL_Renderer* renderer)
{
    m_OpacityBox.Draw(renderer);
    m_BackgroundBox.Draw(renderer);
    m_Title.Draw(renderer);

    m_GameOverText.Draw(renderer);
    m_RestartGameButton.Draw(renderer);

}


// -------------------------------------------------------
// -------------------------------------------------------
void GameOverScreen::Initialize()
{
    m_OpacityBox.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_OpacityBox.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_OpacityBox.SetSize(CoreManagers::g_SettingsManager.GetScreenWidth(), CoreManagers::g_SettingsManager.GetScreenHeight());
    m_OpacityBox.SetColor(g_GameGlobals.COLOR_BLACK);
    m_OpacityBox.SetDisplayType(DisplayType::eDisabled);

    m_BackgroundBox.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_BackgroundBox.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_BackgroundBox.SetSize(CoreManagers::g_SettingsManager.GetScreenWidth() / 2, CoreManagers::g_SettingsManager.GetScreenHeight() / 2);
    m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);


    m_Title.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_Title.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_Title.SetOffset(0, CoreManagers::g_SettingsManager.GetRelativeScreenY(-200));
    m_Title.SetText("Game Over");
    m_Title.SetColor(g_GameGlobals.COLOR_BLACK);

    m_GameOverText.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_GameOverText.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_GameOverText.SetOffset(0, CoreManagers::g_SettingsManager.GetRelativeScreenY(-75));
    m_GameOverText.SetText("Game Over Message.");
    m_GameOverText.SetColor(g_GameGlobals.COLOR_BLACK);

    m_RestartGameButton.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_RestartGameButton.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_RestartGameButton.SetOffset(0, CoreManagers::g_SettingsManager.GetRelativeScreenY(75));
    m_RestartGameButton.SetText("Play Again");
    m_RestartGameButton.SetSize(300,50);

}


// -------------------------------------------------------
// -------------------------------------------------------
void GameOverScreen::OnShow()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameOverScreen::SetGameOverMessage(std::string sMessage)
{
    m_GameOverText.SetText(sMessage);
}

}