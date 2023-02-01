#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/Types/TextBlock.h"
#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/StackPanel.h"
#include "Core/UI/Types/Button.h"
#include "Core/UI/Types/Icon.h"


using namespace CoreUI;

namespace Florida
{
class HUDScreen : public UIScreenBase
{
public:
    HUDScreen();
    ~HUDScreen();

    void Update();
    void Draw(SDL_Renderer* renderer);
    void Initialize();
    void OnShow();

    void UpdateHealthbarUI();
    void UpdateStaminabarUI();
    void UpdateResourcesUI();

    void OnInventoryChangedEvent();
    void OnPlayerHealthChangedEvent();
    void OnPlayerEquippedItemChangedEvent();
    void OnDayCountChangedEvent();
    void OnAmmoCountChangedEvent();
    void OnStaminaPotionUsedEvent();


private:

    const uint16_t m_uiBarMaxWidth = 196;
    const uint16_t m_uiBarMaxHeight = 21;

    Icon m_HealthIcon;
    Box m_HealthBarBackground;
    Box m_HealthBar;

    Icon m_StaminaIcon;
    Box m_StaminaBarBackground;
    Box m_StaminaBar;

    bool m_bHammerEquipped = true;
    Icon m_HammerIcon;
    Icon m_BowIcon;

    StackPanel m_AmmoStack;
    Icon* m_ArrowIcon;
    TextBlock* m_AmmoAmountText;
    Icon* m_StaminaPotionIcon;
    TextBlock* m_StaminaPotionAmountText;

    Icon m_DayIcon;
    Icon m_NightIcon;
    TextBlock m_TimeText;
    TextBlock m_DayCountText;
    Button m_SkipNightButton;

    StackPanel m_ResourceStack;
    Icon m_ScrapIcon;
    Icon m_WoodIcon;
    Icon m_WaterIcon;
    TextBlock m_ScrapAmountText;
    TextBlock m_WoodAmountText;
    TextBlock m_WaterAmountText;

};
}