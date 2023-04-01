#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/Types/TextBlock.h"
#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/Button.h"
#include "Core/UI/Types/Icon.h"
#include "Core/UI/Types/HorizontalStack.h"
#include "Core/UI/Types/VerticalStack.h"


using namespace UI;

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
    void OnDayNightChangedEvent();


private:

    const uint16_t m_uiBarMaxWidth = 196;
    const uint16_t m_uiBarMaxHeight = 21;
    
    VerticalStack m_IconStack;
    Icon m_HealthIcon;
    Icon m_StaminaIcon;
    Icon m_WeaponIcon;

    VerticalStack m_BarBackgroundStack;
    Box m_HealthBarBackground;
    Box m_StaminaBarBackground;

    VerticalStack m_BarStack;
    Box m_HealthBar;
    Box m_StaminaBar;

    HorizontalStack m_AmmoStack;
    Icon m_AmmoIcon;
    TextBlock m_AmmoAmountText;
    
    HorizontalStack m_StaminaPotionStack;
    Icon m_StaminaPotionIcon;
    TextBlock m_StaminaPotionAmountText;

    HorizontalStack m_DayNightStack;
    Icon m_DayNightIcon;
    TextBlock m_TimeText;
    TextBlock m_DayCountText;
    Button m_SkipNightButton;

    HorizontalStack m_ResourceStack;
    Icon m_ScrapIcon;
    Icon m_WoodIcon;
    Icon m_WaterIcon;
    TextBlock m_ScrapAmountText;
    TextBlock m_WoodAmountText;
    TextBlock m_WaterAmountText;

};
}