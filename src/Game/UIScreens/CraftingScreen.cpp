#include "CraftingScreen.h"
#include "Core/Systems/Hash.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/UI/Types/Button.h"
#include "../Player/Player.h"
#include "../Managers/ItemManager.h"
#include "../Managers/EventManager.h"
#include "../Managers/CraftingManager.h"


#define HAMMER_ID "itm_Hammer"
#define SCRAP_ID  "itm_Scrap"
#define WOOD_ID   "itm_Wood"
#define AMMO_ID   "itm_Ammo"

#define SCRAP_ICON   "txt_ScrapIconUI"
#define WATER_ICON   "txt_WaterIconUI"
#define WOOD_ICON    "txt_WoodIconUI"
#define HAMMER_ICON  "txt_HammerIconUI"
#define BOW_ICON     "txt_BowIconUI"
#define ARROW_ICON   "txt_ArrowIconUI"
#define STAMINA_ICON "txt_StaminaPotionIconUI"


namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
CraftingScreen::CraftingScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
CraftingScreen::~CraftingScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::Update()
{
    std::vector<CoreUI::UIBase*> craftingChildren = m_CraftingStack.GetChilren();
    uint32_t uiCraftingStackSize = m_CraftingStack.GetChildrenCount();
    for (uint32_t x=0; x < uiCraftingStackSize; ++x)
    {
        StackPanel* currStack = dynamic_cast<StackPanel*>(craftingChildren[x]); 
        Button* currButton = dynamic_cast<Button*>(currStack->GetChilren()[0]);
        if (currButton)
        {
            currButton->Update(CoreManagers::g_InputManager);

            if (currButton->LeftClickPressed())
            {
                g_CraftingManager.CraftItemByIndex(currButton->GetData1());
            }
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::Draw(SDL_Renderer* renderer)
{
    m_OpacityBox.Draw(renderer);
    m_BackgroundBox.Draw(renderer);

    m_MenuTitleText.Draw(renderer);

    m_ResourceStack.Draw(renderer);

    m_BaseEquipmentStack.Draw(renderer);
    m_InventoryStack.Draw(renderer);

    m_CraftingStack.Draw(renderer);
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::Initialize()
{
    // Backgrounds. 
    m_OpacityBox.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_OpacityBox.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_OpacityBox.SetSize(CoreManagers::g_SettingsManager.GetScreenWidth(), CoreManagers::g_SettingsManager.GetScreenHeight());
    m_OpacityBox.SetColor(g_GameGlobals.COLOR_BLACK);
    m_OpacityBox.SetDisplayType(DisplayType::eDisabled);

    m_BackgroundBox.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_BackgroundBox.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_BackgroundBox.SetSize(CoreManagers::g_SettingsManager.GetScreenWidth() / 2, CoreManagers::g_SettingsManager.GetScreenHeight() - CoreManagers::g_SettingsManager.GetRelativeScreenY(50));
    m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);


    // Title Text.
    m_MenuTitleText.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_MenuTitleText.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_MenuTitleText.SetText("Crafting Menu");
    m_MenuTitleText.SetOffset(0, CoreManagers::g_SettingsManager.GetRelativeScreenY(50));
    m_MenuTitleText.SetColor(g_GameGlobals.COLOR_BLACK);


    // Current Resources.
    m_ScrapIcon.SetTexture(CoreSystems::StringToHash32(std::string(SCRAP_ICON)));
    m_ScrapIcon.SetSize(25, 25);

    m_WoodIcon.SetTexture(CoreSystems::StringToHash32(std::string(WOOD_ICON)));
    m_WoodIcon.SetSize(25, 25);

    m_WaterIcon.SetTexture(CoreSystems::StringToHash32(std::string(WATER_ICON)));
    m_WaterIcon.SetSize(25, 25);

    m_ScrapAmountText.SetText("Scrap");
    m_ScrapAmountText.SetColor(g_GameGlobals.COLOR_BLACK);

    m_WoodAmountText.SetText("Wood");
    m_WoodAmountText.SetColor(g_GameGlobals.COLOR_BLACK);

    m_WaterAmountText.SetText("Water");
    m_WaterAmountText.SetColor(g_GameGlobals.COLOR_BLACK);

    m_ResourceStack.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_ResourceStack.SetChildAlignment(StackpanelAlignment::eHorizontal);
    m_ResourceStack.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_ResourceStack.SetOffset(0, CoreManagers::g_SettingsManager.GetRelativeScreenY(125));
    m_ResourceStack.SetPadding(10);
    m_ResourceStack.AddChild(&m_ScrapIcon);
    m_ResourceStack.AddChild(&m_ScrapAmountText);
    m_ResourceStack.AddChild(&m_WoodIcon);
    m_ResourceStack.AddChild(&m_WoodAmountText);
    m_ResourceStack.AddChild(&m_WaterIcon);
    m_ResourceStack.AddChild(&m_WaterAmountText);

    UpdateResourcesText();


    // Crafting Options.
    m_CraftingStack.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_CraftingStack.SetChildAlignment(StackpanelAlignment::eVertical);
    m_CraftingStack.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_CraftingStack.SetOffset(0, CoreManagers::g_SettingsManager.GetRelativeScreenY(-10));
    m_CraftingStack.SetPadding(10);


    // Base Equipment Info.
    m_BaseEquipmentStack.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_BaseEquipmentStack.SetChildAlignment(StackpanelAlignment::eVertical);
    m_BaseEquipmentStack.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_BaseEquipmentStack.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(-150),CoreManagers::g_SettingsManager.GetRelativeScreenY(150));
    m_BaseEquipmentStack.SetPadding(50);


    TextBlock* equipmentTitleText = new TextBlock;
    equipmentTitleText->SetText("Weapons");
    equipmentTitleText->SetColor(g_GameGlobals.COLOR_BLACK);


    const uint32_t uiPrimaryEquippedItemID = g_Player.GetPrimaryEquippedItemID();
    uint32_t uiPrimaryItemIndex = g_ItemManager.m_ItemDataMap[uiPrimaryEquippedItemID];
    ItemData& uiPrimaryItemData = g_ItemManager.m_ItemData[uiPrimaryItemIndex];

    const uint32_t uiSecondaryEquippedItemID = g_Player.GetSecondaryEquippedItemID();
    uint32_t currItemIndex = g_ItemManager.m_ItemDataMap[uiSecondaryEquippedItemID];
    ItemData& uiSecondaryItemData = g_ItemManager.m_ItemData[currItemIndex];


    StackPanel* primaryStack = new StackPanel;
    primaryStack->SetChildAlignment(StackpanelAlignment::eHorizontal);
    primaryStack->SetElementAlignment(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    primaryStack->SetPadding(25);

    Icon* primaryIcon = new Icon;
    primaryIcon->SetSize(25,25);
    if (uiPrimaryItemData.m_sID == HAMMER_ID)
    {
        primaryIcon->SetTexture(CoreSystems::StringToHash32(std::string(HAMMER_ICON)));
    }
    else
    {
        primaryIcon->SetTexture(CoreSystems::StringToHash32(std::string(BOW_ICON)));
    }
    
    Icon* secondaryIcon = new Icon;
    secondaryIcon->SetSize(25,25);
    if (uiSecondaryItemData.m_sID == HAMMER_ID)
    {
        secondaryIcon->SetTexture(CoreSystems::StringToHash32(std::string(HAMMER_ICON)));
    }
    else
    {
        secondaryIcon->SetTexture(CoreSystems::StringToHash32(std::string(BOW_ICON)));
    }
    
    primaryStack->AddChild(primaryIcon);
    primaryStack->AddChild(secondaryIcon);

    m_BaseEquipmentStack.AddChild(equipmentTitleText);
    m_BaseEquipmentStack.AddChild(primaryStack);


    // Inventory Disposable Info.
    m_InventoryStack.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eCenter);
    m_InventoryStack.SetChildAlignment(StackpanelAlignment::eVertical);
    m_InventoryStack.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_InventoryStack.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(150), CoreManagers::g_SettingsManager.GetRelativeScreenY(150));
    m_InventoryStack.SetPadding(50);

    TextBlock* newResourceText = new TextBlock;
    newResourceText->SetText(std::string("Disposable Items"));
    newResourceText->SetColor(g_GameGlobals.COLOR_BLACK);

    StackPanel* ammoStack = new StackPanel;
    ammoStack->SetChildAlignment(StackpanelAlignment::eHorizontal);
    ammoStack->SetElementAlignment(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    ammoStack->SetPadding(25);

    Icon* ammoIcon = new Icon;
    ammoIcon->SetSize(25,25);
    ammoIcon->SetTexture(CoreSystems::StringToHash32(std::string(ARROW_ICON)));

    Icon* staminaPotionIcon = new Icon;
    staminaPotionIcon->SetSize(25,25);
    staminaPotionIcon->SetTexture(CoreSystems::StringToHash32(std::string(STAMINA_ICON)));

    m_AmmoAmountText.SetText("NUMBER");
    m_AmmoAmountText.SetColor(g_GameGlobals.COLOR_BLACK);

    ammoStack->AddChild(ammoIcon);
    ammoStack->AddChild(&m_AmmoAmountText);

    m_StaminaPotionAmountText.SetText("NUMBER");
    m_StaminaPotionAmountText.SetColor(g_GameGlobals.COLOR_BLACK);

    ammoStack->AddChild(staminaPotionIcon);
    ammoStack->AddChild(&m_StaminaPotionAmountText);

    m_InventoryStack.AddChild(newResourceText);
    m_InventoryStack.AddChild(ammoStack);


    g_EventManager.Subscribe(Events::eInventoryChanged, [this]() { CraftingScreen::OnInventoryChangedEvent(); });
    g_EventManager.Subscribe(Events::eAmmoChanged, [this]() { CraftingScreen::OnAmmoCountChangedEvent(); });
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::OnShow()
{
    UpdateResourcesText();
    UpdateCraftingText();
    UpdateDisposablesText();
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::UpdateResourcesText()
{
    std::vector<InventoryItemData> vPlayerInventory = g_Player.GetPlayerInventoryAll();
    const uint32_t uiItemSize = static_cast<uint32_t>(vPlayerInventory.size());
    for (uint32_t x = 0; x < uiItemSize; ++x)
    {
        InventoryItemData& currInventoryItem = vPlayerInventory[x];
        uint32_t currItemIndex = g_ItemManager.m_ItemDataMap[currInventoryItem.m_uiID];
        ItemData& currItem = g_ItemManager.m_ItemData[currItemIndex];

        if (currItem.m_Type == ItemType::eResource)
        {
            std::string resourceText = std::to_string(currInventoryItem.m_uiAmount);

            if (currItem.m_sID == SCRAP_ID)
            {
                m_ScrapAmountText.SetText(resourceText);
            }
            else if (currItem.m_sID == WOOD_ID)
            {
                m_WoodAmountText.SetText(resourceText);
            }
            else
            {
                m_WaterAmountText.SetText(resourceText);
            }
        }
    }

    m_ResourceStack.RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::UpdateCraftingText()
{
    m_CraftingStack.ClearChildren();

    const std::vector<RecipeData>& RecipesVector = g_CraftingManager.GetAllRecipes();
    const uint8_t RecipesVectorSize = static_cast<uint8_t>(RecipesVector.size());
    for (uint8_t x=0; x < RecipesVectorSize; ++x)
    {
        const RecipeData& currRecipeData = RecipesVector[x];
        const ItemData& rewardItemData = g_ItemManager.GetItemDataByID(currRecipeData.m_Reward.m_uiItemID);
  
        Button* newButton = new Button;
        newButton->SetText(rewardItemData.m_sName);
        newButton->SetSize(200, 50);
        newButton->SetData1(x); // Set Data1 to index of recipe.
        newButton->SetDisplayType(g_CraftingManager.HasEnoughResourcesToCraft(currRecipeData.m_uiRecipeID) ? DisplayType::eVisible : DisplayType::eDisabled);

        TextBlock* newText = new TextBlock;
        newText->SetText(currRecipeData.m_sIngredientText);

        StackPanel* newStack = new StackPanel;
        newStack->SetChildAlignment(StackpanelAlignment::eHorizontal);
        newStack->SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
        newStack->SetPadding(25);
        newStack->AddChild(newButton);
        newStack->AddChild(newText);

        m_CraftingStack.AddChild(newStack);
    }

    m_CraftingStack.RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::UpdateDisposablesText()
{
    std::vector<InventoryItemData> vPlayerInventory = g_Player.GetPlayerInventoryAll();
    const uint32_t uiItemSize = static_cast<uint32_t>(vPlayerInventory.size());
    for (uint32_t x = 0; x < uiItemSize; ++x)
    {
        InventoryItemData& currInventoryItem = vPlayerInventory[x];
        uint32_t currItemIndex = g_ItemManager.m_ItemDataMap[currInventoryItem.m_uiID];
        ItemData& currItem = g_ItemManager.m_ItemData[currItemIndex];

        if (currItem.m_Type == ItemType::eDisposable)
        {
            if (currItem.m_sID == AMMO_ID)
            {
                m_AmmoAmountText.SetText(std::to_string(currInventoryItem.m_uiAmount));
            }
            else
            {
                m_StaminaPotionAmountText.SetText(std::to_string(currInventoryItem.m_uiAmount));
            }
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::OnInventoryChangedEvent()
{
    UpdateCraftingText();
    UpdateResourcesText();
    UpdateDisposablesText();
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::OnAmmoCountChangedEvent()
{
}

}