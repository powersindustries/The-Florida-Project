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
}


// -------------------------------------------------------
// -------------------------------------------------------
ControlsScreen::~ControlsScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void ControlsScreen::Update()
{
    m_XButton.Update(CoreManagers::g_InputManager);

    if (m_XButton.LeftClickPressed())
    {
        g_UIManager.ActivateControlsScreen();
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
    m_StackPanel.Draw(renderer);
}


// -------------------------------------------------------
// -------------------------------------------------------
void ControlsScreen::Initialize()
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
    m_Title.SetText("Controls");
    m_Title.SetColor(g_GameGlobals.COLOR_BLACK);

    m_XButton.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_XButton.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_XButton.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(400), CoreManagers::g_SettingsManager.GetRelativeScreenY(50));
    m_XButton.SetText("X");
    m_XButton.SetSize(50, 50);

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

    m_StackPanel.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eBottom);
    m_StackPanel.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_StackPanel.AddChild(movementText);
    m_StackPanel.AddChild(attackText);
    m_StackPanel.AddChild(sprintText);
    m_StackPanel.AddChild(changeWeaponsText);
    m_StackPanel.AddChild(staminaPotionText);
    m_StackPanel.AddChild(interactText);
    m_StackPanel.AddChild(escText);
    m_StackPanel.AddChild(craftText);
    m_StackPanel.SetPadding(75);
    m_StackPanel.SetOffset(0, CoreManagers::g_SettingsManager.GetRelativeScreenY(125));

}


// -------------------------------------------------------
// -------------------------------------------------------
void ControlsScreen::OnShow()
{
}

}
