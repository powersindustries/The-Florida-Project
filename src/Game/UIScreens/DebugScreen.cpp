#include "DebugScreen.h"
#include "GameGlobals.h"

#include "Core/Systems/Systems.h"
#include "Core/Systems/Hash.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/Managers/InputManager.h"

#include "../Player/Player.h"
#include "../Managers/EventManager.h"
#include "../Managers/GameplayManager.h"
#include "../Managers/ItemManager.h"
#include "../Managers/UIManager.h"

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
void DebugScreen::Initialize()
{
	m_BackgroundBox.SetAnchor(Anchor::eTopRight);
	m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);
	m_BackgroundBox.SetSize(400, Core::g_SettingsManager.GetScreenHeight() - 50);
	m_BackgroundBox.SetOffset(
		-10,
		10
	);

	m_DamageButton.SetText("Damage Player");
	m_DamageButton.SetSize(300, 50);

	m_HealButton.SetText("Heal Player");
	m_HealButton.SetSize(300, 50);

	m_ScrapButton.SetText("Increase Scrap");
	m_ScrapButton.SetSize(300, 50);

	m_WoodButton.SetText("Increase Wood");
	m_WoodButton.SetSize(300, 50);

	m_WaterButton.SetText("Increase Water");
	m_WaterButton.SetSize(300, 50);

	m_IncreaseTimeButton.SetText("Increase Time");
	m_IncreaseTimeButton.SetSize(300, 50);

	m_MainStack.SetAnchor(Anchor::eCenterRight);
	m_MainStack.SetPadding(10);
	m_MainStack.AddChild(&m_DamageButton);
	m_MainStack.AddChild(&m_HealButton);
	m_MainStack.AddChild(&m_ScrapButton);
	m_MainStack.AddChild(&m_WoodButton);
	m_MainStack.AddChild(&m_WaterButton);
	m_MainStack.AddChild(&m_IncreaseTimeButton);
	m_MainStack.SetOffset(
		-50,
		((m_MainStack.GetHeight() / 2) * -1)
	);
}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::Update()
{
    m_DamageButton.Update();
    m_HealButton.Update();
    m_ScrapButton.Update();
    m_WoodButton.Update();
    m_WaterButton.Update();
    m_IncreaseTimeButton.Update();


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
void DebugScreen::OnShow()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::RemoveSelf()
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
    g_ItemManager.AddItem(Core::StringToHash32(std::string("itm_Scrap")), 1);
}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::OnIncreaseWoodButton()
{
    g_ItemManager.AddItem(Core::StringToHash32(std::string("itm_Wood")), 1);
}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::OnIncreaseWaterButton()
{
    g_ItemManager.AddItem(Core::StringToHash32(std::string("itm_Water")), 1);
}


// -------------------------------------------------------
// -------------------------------------------------------
void DebugScreen::OnIncreaseTimeButton()
{
    g_GameplayManager.DEBUG_IncreaseTimeOneHour();
}

}