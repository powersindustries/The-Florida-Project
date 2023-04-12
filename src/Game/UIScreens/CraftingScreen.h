#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/UIScreenBase.h"

#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/TextBlock.h"
#include "Core/UI/Types/Icon.h"
#include "Core/UI/Types/HorizontalStack.h"
#include "Core/UI/Types/Button.h"

using namespace UI;

namespace Florida
{

class CraftingScreen : public UIScreenBase
{
public:
    CraftingScreen();
    ~CraftingScreen();

    void Initialize();

    void Update();
    void Draw(SDL_Renderer* renderer);

    void OnShow();
    void RemoveSelf();


private:

    void UpdateResourcesText();
    void UpdateCraftingText();
    void UpdateDisposablesText();

    void OnInventoryChangedEvent();
    void OnAmmoCountChangedEvent();


private:

    Box m_OpacityBox;
    Box m_BackgroundBox;

    TextBlock m_MenuTitleText;

    HorizontalStack m_ResourceStack;
    Icon m_ScrapIcon;
    Icon m_WoodIcon;
    Icon m_WaterIcon;
    TextBlock m_ScrapAmountText;
    TextBlock m_WoodAmountText;
    TextBlock m_WaterAmountText;

    HorizontalStack m_AmmoCraftingStack;
    Button m_AmmoCraftButton;
    TextBlock m_AmmoCraftText;

    HorizontalStack m_StaminaCraftingStack;
    Button m_StaminaCraftButton;
    TextBlock m_StaminaCraftText;

    HorizontalStack m_InventoryStack;
    TextBlock m_InventoryTitleText;
    TextBlock m_AmmoAmountText;
    TextBlock m_StaminaPotionAmountText;

};

}