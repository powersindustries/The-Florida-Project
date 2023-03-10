#include "DebugScreen.h"
#include "GameGlobals.h"
#include "Core/Systems/Systems.h"
#include "../Player/Player.h"
#include "../Managers/EventManager.h"
#include "Core/Systems/Hash.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/Managers/InputManager.h"
#include "../Managers/GameplayManager.h"
#include "../Managers/ItemManager.h"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
DebugScreen::DebugScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
DebugScreen::~DebugScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::Update()
{
    m_DamageButton.Update(CoreManagers::g_InputManager);
    m_HealButton.Update(CoreManagers::g_InputManager);
    m_ScrapButton.Update(CoreManagers::g_InputManager);
    m_WoodButton.Update(CoreManagers::g_InputManager);
    m_WaterButton.Update(CoreManagers::g_InputManager);
    m_IncreaseTimeButton.Update(CoreManagers::g_InputManager);


    if (m_DamageButton.LeftClickPressed())
    {
        OnDamageButton();
    }

    if (m_HealButton.LeftClickPressed())
    {
        OnHealButton();
    }

    if (m_ScrapButton.LeftClickPressed())
    {
        OnIncreaseScrapButton();
    }

    if (m_WoodButton.LeftClickPressed())
    {
        OnIncreaseWoodButton();
    }

    if (m_WaterButton.LeftClickPressed())
    {
        OnIncreaseWaterButton();
    }

    if (m_IncreaseTimeButton.LeftClickPressed())
    {
        OnIncreaseTimeButton();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::Draw(SDL_Renderer* renderer)
{
    m_BackgroundBox.Draw(renderer);
    m_MainStack.Draw(renderer);
}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::Initialize()
{
    m_BackgroundBox.SetAnchor(HorizontalAlignment::eRight, VerticalAlignment::eCenter);
    m_BackgroundBox.SetElementAlignment(HorizontalAlignment::eLeft, VerticalAlignment::eCenter);
    m_BackgroundBox.SetOffset(25, 0);
    m_BackgroundBox.SetSize(500, CoreManagers::g_SettingsManager.GetScreenHeight() - 50);
    m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);


    m_DamageButton.SetText("Damage Player");
    m_DamageButton.SetSize(300, 30);

    m_HealButton.SetText("Heal Player");
    m_HealButton.SetSize(300, 30);

    m_ScrapButton.SetText("Increase Scrap");
    m_ScrapButton.SetSize(300, 30);

    m_WoodButton.SetText("Increase Wood");
    m_WoodButton.SetSize(300, 30);

    m_WaterButton.SetText("Increase Water");
    m_WaterButton.SetSize(300, 30);

    m_IncreaseTimeButton.SetText("Increase Time");
    m_IncreaseTimeButton.SetSize(300, 30);


    m_MainStack.SetAnchor(HorizontalAlignment::eRight, VerticalAlignment::eTop);
    m_MainStack.SetElementAlignment(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    m_MainStack.SetOffset(100, 50);
    m_MainStack.SetPadding(10);
    m_MainStack.AddChild(&m_DamageButton);
    m_MainStack.AddChild(&m_HealButton);
    m_MainStack.AddChild(&m_ScrapButton);
    m_MainStack.AddChild(&m_WoodButton);
    m_MainStack.AddChild(&m_WaterButton);
    m_MainStack.AddChild(&m_IncreaseTimeButton);

}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::OnShow()
{

}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::OnDamageButton()
{
    g_Player.TakeDamage(1);
}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::OnHealButton()
{
    g_Player.Heal(1);
}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::OnIncreaseScrapButton()
{
    g_ItemManager.AddItem(CoreSystems::StringToHash32(std::string("itm_Scrap")), 1);
}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::OnIncreaseWoodButton()
{
    g_ItemManager.AddItem(CoreSystems::StringToHash32(std::string("itm_Wood")), 1);
}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::OnIncreaseWaterButton()
{
    g_ItemManager.AddItem(CoreSystems::StringToHash32(std::string("itm_Water")), 1);
}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::OnIncreaseTimeButton()
{
    g_GameplayManager.DEBUG_IncreaseTimeOneHour();
}

}