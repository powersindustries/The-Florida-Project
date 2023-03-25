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
    m_RestartGameButton.Update();

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
    m_OpacityBox.SetAnchor(Anchor::eTopLeft);
    m_OpacityBox.SetColor(g_GameGlobals.COLOR_BLACK);
    m_OpacityBox.SetSize(CoreManagers::g_SettingsManager.GetScreenWidth(), CoreManagers::g_SettingsManager.GetScreenHeight());
    m_OpacityBox.SetVisibility(UIVisibility::eDisabled);

    m_BackgroundBox.SetAnchor(Anchor::eCenter);
    m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);
    m_BackgroundBox.SetSize(
        CoreManagers::g_SettingsManager.GetScreenWidth() / 2, 
        CoreManagers::g_SettingsManager.GetScreenHeight() / 2
    );
    m_BackgroundBox.SetOffset(
		((m_BackgroundBox.GetWidth() / 2) * -1),
		((m_BackgroundBox.GetHeight() / 2) * -1)
	);

    m_Title.SetAnchor(Anchor::eCenter);
    m_Title.SetColor(g_GameGlobals.COLOR_BLACK);
    m_Title.SetText("Game Over");
    m_Title.SetSize(400, 100);
    m_Title.SetOffset(
		((m_Title.GetWidth() / 2) * -1),
        -200
    );

    m_GameOverText.SetAnchor(Anchor::eCenter);
    m_GameOverText.SetColor(g_GameGlobals.COLOR_BLACK);
    m_GameOverText.SetText("Game Over Message.");
    m_GameOverText.SetOffset(
		((m_GameOverText.GetWidth() / 2) * -1),
        -75
    );

    m_RestartGameButton.SetAnchor(Anchor::eCenter);
    m_RestartGameButton.SetText("Play Again");
    m_RestartGameButton.SetSize(300,50);
    m_RestartGameButton.SetOffset(
		((m_RestartGameButton.GetWidth() / 2) * -1),
        75
    );

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
    m_GameOverText.SetOffset(
		((m_GameOverText.GetWidth() / 2) * -1),
        -75
    );
}

}