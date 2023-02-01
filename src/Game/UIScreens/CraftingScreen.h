#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/StackPanel.h"
#include "Core/UI/Types/TextBlock.h"
#include "Core/UI/Types/Icon.h"

using namespace CoreUI;

namespace Florida
{
class CraftingScreen : public UIScreenBase
{
public:
    CraftingScreen();
    ~CraftingScreen();

    void Update();
    void Draw(SDL_Renderer* renderer);
    void Initialize();
    void OnShow();


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

    StackPanel m_ResourceStack;
    Icon m_ScrapIcon;
    Icon m_WoodIcon;
    Icon m_WaterIcon;
    TextBlock m_ScrapAmountText;
    TextBlock m_WoodAmountText;
    TextBlock m_WaterAmountText;

    StackPanel m_CraftingStack;
    
    StackPanel m_BaseEquipmentStack;

    StackPanel m_InventoryStack;
    TextBlock m_AmmoAmountText;
    TextBlock m_StaminaPotionAmountText;

};
}