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
    m_ScreenID = UIScreenID::eIntro;
}


// -------------------------------------------------------
// -------------------------------------------------------
IntroScreen::~IntroScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void IntroScreen::Initialize()
{
	m_OpacityBox.SetAnchor(Anchor::eTopLeft);
	m_OpacityBox.SetColor(g_GameGlobals.COLOR_BLACK);
	m_OpacityBox.SetSize(Core::g_SettingsManager.GetScreenWidth(), Core::g_SettingsManager.GetScreenHeight());
	m_OpacityBox.SetVisibility(UIVisibility::eDisabled);

	m_BackgroundBox.SetAnchor(Anchor::eTopCenter);
	m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);
	m_BackgroundBox.SetSize(
		Core::g_SettingsManager.GetScreenWidth() / 2,
		Core::g_SettingsManager.GetScreenHeight() - Core::g_SettingsManager.GetRelativeScreenY(50));
	m_BackgroundBox.SetOffset(
		((m_BackgroundBox.GetWidth() / 2) * -1),
		Core::g_SettingsManager.GetRelativeScreenY(25)
	);

	m_GameLogo.SetAnchor(Anchor::eTopCenter);
	m_GameLogo.SetTexture(Core::StringToHash32(std::string(FLORIDALOGO_ID)));
	m_GameLogo.SetSize(500, 300);
	m_GameLogo.SetOffset(
		((m_GameLogo.GetWidth() / 2) * -1),
		Core::g_SettingsManager.GetRelativeScreenY(250)
	);

	m_StartGameButton.SetText("START NEW GAME");
	m_StartGameButton.SetSize(300, 50);

	m_ControlsButton.SetText("CONTROLS");
	m_ControlsButton.SetSize(300, 50);

	m_ExitGameButton.SetText("EXIT GAME");
	m_ExitGameButton.SetSize(300, 50);

	m_VerticalStack.SetAnchor(Anchor::eBottomCenter);
	m_VerticalStack.SetPadding(50);
	m_VerticalStack.AddChild(&m_StartGameButton);
	m_VerticalStack.AddChild(&m_ControlsButton);
	m_VerticalStack.AddChild(&m_ExitGameButton);
	m_VerticalStack.SetOffset(
		((m_VerticalStack.GetWidth() / 2) * -1),
		Core::g_SettingsManager.GetRelativeScreenY(-100)
	);

}


// -------------------------------------------------------
// -------------------------------------------------------
void IntroScreen::Update()
{
    m_StartGameButton.Update();
    m_ControlsButton.Update();
    m_ExitGameButton.Update();

    if (m_StartGameButton.LeftClickPressed())
    {
        g_GameManager.SetIntroScreen(true);
        g_GameManager.StartNewGame();
    }
    
    if (m_ControlsButton.LeftClickPressed())
    {
        g_UIManager.ActivateScreen(UIScreenID::eControls);
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

    m_VerticalStack.Draw(renderer);

}


// -------------------------------------------------------
// -------------------------------------------------------
void IntroScreen::OnShow()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void IntroScreen::RemoveSelf()
{
    g_UIManager.RemoveScreen(m_ScreenID);
}

}