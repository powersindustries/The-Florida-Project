#include "ControlsScreen.h"
#include "GameGlobals.h"
#include "Core/Managers/SettingsManager.h"
#include "../Managers/UIManager.h"


namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
ControlsScreen::ControlsScreen()
{
    m_ScreenID = UI::UIScreenID::eControls;
}


// -------------------------------------------------------
// -------------------------------------------------------
ControlsScreen::~ControlsScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void ControlsScreen::Initialize()
{
	m_OpacityBox.SetAnchor(Anchor::eTopLeft);
	m_OpacityBox.SetColor(g_GameGlobals.COLOR_BLACK);
	m_OpacityBox.SetSize(Core::g_SettingsManager.GetScreenWidth(), Core::g_SettingsManager.GetScreenHeight());
	m_OpacityBox.SetVisibility(UIVisibility::eDisabled);

	m_BackgroundBox.SetAnchor(Anchor::eTopCenter);
	m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);
	m_BackgroundBox.SetSize(
		Core::g_SettingsManager.GetScreenWidth() / 2,
		Core::g_SettingsManager.GetScreenHeight() - Core::g_SettingsManager.GetRelativeScreenY(50)
	);
	m_BackgroundBox.SetOffset(
		((m_BackgroundBox.GetWidth() / 2) * -1),
		0
	);

	m_Title.SetAnchor(Anchor::eTopCenter);
	m_Title.SetText("Controls");
	m_Title.SetOffset(
		((m_Title.GetWidth() / 2) * -1),
		Core::g_SettingsManager.GetRelativeScreenY(75)
	);

	m_XButton.SetAnchor(Anchor::eTopCenter);
	m_XButton.SetText("X");
	m_XButton.SetSize(50, 50);
	m_XButton.SetOffset(
		Core::g_SettingsManager.GetRelativeScreenX(400),
		Core::g_SettingsManager.GetRelativeScreenY(50)
	);

	TextBlock* movementText = new TextBlock;
	movementText->SetText("W,A,S,D - Movement");

	TextBlock* attackText = new TextBlock;
	attackText->SetText("Left Click - Attack");

	TextBlock* changeWeaponsText = new TextBlock;
	changeWeaponsText->SetText("Q - Change Weapons");

	TextBlock* sprintText = new TextBlock;
	sprintText->SetText("SPACE BAR - Sprint");

	TextBlock* staminaPotionText = new TextBlock;
	staminaPotionText->SetText("R - Use Stamina Potion");

	TextBlock* interactText = new TextBlock;
	interactText->SetText("Hold E - Pickup Resource");

	TextBlock* escText = new TextBlock;
	escText->SetText("ESC - Open Main Menu");

	TextBlock* craftText = new TextBlock;
	craftText->SetText("TAB - Open Crafting Menu");

	m_VerticalStack.SetAnchor(Anchor::eTopCenter);
	m_VerticalStack.SetPadding(75);
	m_VerticalStack.AddChild(movementText);
	m_VerticalStack.AddChild(attackText);
	m_VerticalStack.AddChild(sprintText);
	m_VerticalStack.AddChild(changeWeaponsText);
	m_VerticalStack.AddChild(staminaPotionText);
	m_VerticalStack.AddChild(interactText);
	m_VerticalStack.AddChild(escText);
	m_VerticalStack.AddChild(craftText);
	m_VerticalStack.SetOffset(
		((m_VerticalStack.GetWidth() / 2) * -1),
		Core::g_SettingsManager.GetRelativeScreenY(200)
	);

}


// -------------------------------------------------------
// -------------------------------------------------------
void ControlsScreen::Update()
{
    m_XButton.Update();

    if (m_XButton.LeftClickPressed())
    {
		RemoveSelf();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void ControlsScreen::Draw(SDL_Renderer* renderer)
{
    m_OpacityBox.Draw(renderer);
    m_BackgroundBox.Draw(renderer);
    m_Title.Draw(renderer);
    m_XButton.Draw(renderer);
    m_VerticalStack.Draw(renderer);
}


// -------------------------------------------------------
// -------------------------------------------------------
void ControlsScreen::OnShow()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void ControlsScreen::RemoveSelf()
{
	g_UIManager.RemoveScreen(m_ScreenID);
}

}
