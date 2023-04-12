#include "CraftingScreen.h"

#include "Core/Systems/Hash.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/UI/Types/Button.h"

#include "../Player/Player.h"

#include "../Managers/UIManager.h"
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
    m_ScreenID = UIScreenID::eInventory;
}


// -------------------------------------------------------
// -------------------------------------------------------
CraftingScreen::~CraftingScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::Initialize()
{
	// Backgrounds. 
	m_OpacityBox.SetAnchor(Anchor::eTopLeft);
	m_OpacityBox.SetSize(Core::g_SettingsManager.GetScreenWidth(), Core::g_SettingsManager.GetScreenHeight());
	m_OpacityBox.SetColor(g_GameGlobals.COLOR_BLACK);
	m_OpacityBox.SetVisibility(UIVisibility::eDisabled);

	m_BackgroundBox.SetAnchor(Anchor::eCenter);
	m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);
	m_BackgroundBox.SetSize(
		Core::g_SettingsManager.GetScreenWidth() / 2,
		Core::g_SettingsManager.GetScreenHeight() - Core::g_SettingsManager.GetRelativeScreenY(50)
	);
	m_BackgroundBox.SetOffset(
		((m_BackgroundBox.GetWidth() / 2) * -1),
		((m_BackgroundBox.GetHeight() / 2) * -1)
	);

	// Title Text.
	m_MenuTitleText.SetAnchor(Anchor::eTopCenter);
	m_MenuTitleText.SetColor(g_GameGlobals.COLOR_BLACK);
	m_MenuTitleText.SetText("Crafting Menu");
	m_MenuTitleText.SetOffset(
		((m_MenuTitleText.GetWidth() / 2) * -1),
		Core::g_SettingsManager.GetRelativeScreenY(50)
	);

	// Current Resources.
	m_ScrapIcon.SetTexture(Core::StringToHash32(std::string(SCRAP_ICON)));
	m_ScrapIcon.SetSize(25, 25);

	m_WoodIcon.SetTexture(Core::StringToHash32(std::string(WOOD_ICON)));
	m_WoodIcon.SetSize(25, 25);

	m_WaterIcon.SetTexture(Core::StringToHash32(std::string(WATER_ICON)));
	m_WaterIcon.SetSize(25, 25);

	m_ScrapAmountText.SetText("scrap");
	m_ScrapAmountText.SetColor(g_GameGlobals.COLOR_BLACK);

	m_WoodAmountText.SetText("wood");
	m_WoodAmountText.SetColor(g_GameGlobals.COLOR_BLACK);

	m_WaterAmountText.SetText("water");
	m_WaterAmountText.SetColor(g_GameGlobals.COLOR_BLACK);

	m_ResourceStack.SetAnchor(Anchor::eTopCenter);
	m_ResourceStack.SetPadding(10);
	m_ResourceStack.AddChild(&m_ScrapIcon);
	m_ResourceStack.AddChild(&m_ScrapAmountText);
	m_ResourceStack.AddChild(&m_WoodIcon);
	m_ResourceStack.AddChild(&m_WoodAmountText);
	m_ResourceStack.AddChild(&m_WaterIcon);
	m_ResourceStack.AddChild(&m_WaterAmountText);
	m_ResourceStack.SetOffset(
		((m_ResourceStack.GetWidth() / 2) * -1),
		Core::g_SettingsManager.GetRelativeScreenY(100)
	);

	UpdateResourcesText();

	// Crafting Options.
	m_AmmoCraftButton.SetText("Craft Ammo");
	m_AmmoCraftButton.SetSize(200, 35);

	m_AmmoCraftText.SetColor(g_GameGlobals.COLOR_BLACK);
	m_AmmoCraftText.SetText("Ammo Text");

	m_AmmoCraftingStack.SetAnchor(Anchor::eTopCenter);
	m_AmmoCraftingStack.SetPadding(10);
	m_AmmoCraftingStack.AddChild(&m_AmmoCraftButton);
	m_AmmoCraftingStack.AddChild(&m_AmmoCraftText);

	m_StaminaCraftButton.SetText("Craft Stamina Potion");
	m_StaminaCraftButton.SetSize(200, 35);

	m_StaminaCraftText.SetColor(g_GameGlobals.COLOR_BLACK);
	m_StaminaCraftText.SetText("Stamina Text");

	m_StaminaCraftingStack.SetAnchor(Anchor::eTopCenter);
	m_StaminaCraftingStack.SetPadding(10);
	m_StaminaCraftingStack.AddChild(&m_StaminaCraftButton);
	m_StaminaCraftingStack.AddChild(&m_StaminaCraftText);

	// Inventory Disposable Info.
	m_InventoryTitleText.SetAnchor(Anchor::eCenter);
	m_InventoryTitleText.SetColor(g_GameGlobals.COLOR_BLACK);
	m_InventoryTitleText.SetText(std::string("Disposable Items"));
	m_InventoryTitleText.SetOffset(
		((m_InventoryTitleText.GetWidth() / 2) * -1),
		-100
	);

	Icon* ammoIcon = new Icon;
	ammoIcon->SetSize(25, 25);
	ammoIcon->SetTexture(Core::StringToHash32(std::string(ARROW_ICON)));

	Icon* staminaPotionIcon = new Icon;
	staminaPotionIcon->SetSize(25, 25);
	staminaPotionIcon->SetTexture(Core::StringToHash32(std::string(STAMINA_ICON)));

	m_AmmoAmountText.SetText("NUMBER");
	m_AmmoAmountText.SetColor(g_GameGlobals.COLOR_BLACK);

	m_StaminaPotionAmountText.SetText("NUMBER");
	m_StaminaPotionAmountText.SetColor(g_GameGlobals.COLOR_BLACK);

	m_InventoryStack.SetAnchor(Anchor::eCenter);
	m_InventoryStack.SetPadding(50);
	m_InventoryStack.AddChild(ammoIcon);
	m_InventoryStack.AddChild(&m_AmmoAmountText);
	m_InventoryStack.AddChild(staminaPotionIcon);
	m_InventoryStack.AddChild(&m_StaminaPotionAmountText);


	g_EventManager.Subscribe(Events::eInventoryChanged, [this]() { CraftingScreen::OnInventoryChangedEvent(); });
	g_EventManager.Subscribe(Events::eAmmoChanged, [this]() { CraftingScreen::OnAmmoCountChangedEvent(); });
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::Update()
{
    m_AmmoCraftButton.Update();
	if (m_AmmoCraftButton.LeftClickPressed())
	{
		g_CraftingManager.CraftItemByIndex(m_AmmoCraftButton.GetData1());
	}

    m_StaminaCraftButton.Update();
	if (m_StaminaCraftButton.LeftClickPressed())
	{
		g_CraftingManager.CraftItemByIndex(m_StaminaCraftButton.GetData1());
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
    m_AmmoCraftingStack.Draw(renderer);
    m_StaminaCraftingStack.Draw(renderer);

    m_InventoryTitleText.Draw(renderer);
    m_InventoryStack.Draw(renderer);
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
void CraftingScreen::RemoveSelf()
{
    g_UIManager.RemoveScreen(m_ScreenID);
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::UpdateResourcesText()
{
    const uint32_t uiScrapID = Core::StringToHash32(std::string(SCRAP_ID));
    const uint32_t uiWoodID = Core::StringToHash32(std::string(WOOD_ID));

    const std::vector<ItemData> vPlayerInventory = g_ItemManager.GetAllItemData();
    const uint32_t uiItemSize = static_cast<uint32_t>(vPlayerInventory.size());
    for (uint32_t x = 0; x < uiItemSize; ++x)
    {
        const ItemData& currItem = vPlayerInventory[x];

        if (currItem.m_Type == ItemType::eResource)
        {
            std::string resourceText = std::to_string(currItem.m_uiAmount);

            if (currItem.m_uiID == uiScrapID)
            {
                m_ScrapAmountText.SetText(resourceText);
            }
            else if (currItem.m_uiID == uiWoodID)
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
	m_ResourceStack.SetOffset(
		((m_ResourceStack.GetWidth() / 2) * -1),
		Core::g_SettingsManager.GetRelativeScreenY(100)
	);
}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::UpdateCraftingText()
{
    const std::vector<RecipeData>& RecipesVector = g_CraftingManager.GetAllRecipes();
    const uint8_t uiRecipesVectorSize = static_cast<uint8_t>(RecipesVector.size());
    for (uint8_t x=0; x < uiRecipesVectorSize; ++x)
    {
        const RecipeData& currRecipeData = RecipesVector[x];
        const ItemData& rewardItemData = g_ItemManager.GetItemDataByID(currRecipeData.m_Reward.m_uiItemID);
 
        if (rewardItemData.m_uiID == Core::StringToHash32(std::string("itm_Ammo")))
        {
            m_AmmoCraftButton.SetText(rewardItemData.m_sName);
            m_AmmoCraftButton.SetData1(x); // Set Data1 to recipe index.
            m_AmmoCraftButton.SetVisibility(g_CraftingManager.HasEnoughResourcesToCraft(currRecipeData.m_uiRecipeID) ? UIVisibility::eVisible : UIVisibility::eDisabled);

            m_AmmoCraftText.SetText(currRecipeData.m_sIngredientText);
        }
        else if (rewardItemData.m_uiID == Core::StringToHash32(std::string("itm_StaminaPotion")))
        {

            m_StaminaCraftButton.SetText(rewardItemData.m_sName);
            m_StaminaCraftButton.SetData1(x); // Set Data1 to recipe index.
            m_StaminaCraftButton.SetVisibility(g_CraftingManager.HasEnoughResourcesToCraft(currRecipeData.m_uiRecipeID) ? UIVisibility::eVisible : UIVisibility::eDisabled);

            m_StaminaCraftText.SetText(currRecipeData.m_sIngredientText);
        }
    }

    m_AmmoCraftingStack.RefreshUI();
    m_AmmoCraftingStack.SetOffset(
		( (m_AmmoCraftingStack.GetWidth() / 2) * -1 ),
		Core::g_SettingsManager.GetRelativeScreenY(200)
    );

    m_StaminaCraftingStack.RefreshUI();
    m_StaminaCraftingStack.SetOffset(
		( (m_StaminaCraftingStack.GetWidth() / 2) * -1 ),
		Core::g_SettingsManager.GetRelativeScreenY(300)
    );

}


// -------------------------------------------------------
// -------------------------------------------------------
void CraftingScreen::UpdateDisposablesText()
{
	const uint32_t uiAmmoID = Core::StringToHash32(std::string(AMMO_ID));

	const std::vector<ItemData> vPlayerInventory = g_ItemManager.GetAllItemData();
	const uint32_t uiItemSize = static_cast<uint32_t>(vPlayerInventory.size());
	for (uint32_t x = 0; x < uiItemSize; ++x)
	{
		const ItemData& currItem = vPlayerInventory[x];

		if (currItem.m_Type == ItemType::eDisposable)
		{
			if (currItem.m_uiID == uiAmmoID)
			{
				m_AmmoAmountText.SetText(std::to_string(currItem.m_uiAmount));
			}
			else
			{
				m_StaminaPotionAmountText.SetText(std::to_string(currItem.m_uiAmount));
			}
		}
	}

	m_InventoryStack.RefreshUI();
	m_InventoryStack.SetOffset(
		((m_InventoryStack.GetWidth() / 2) * -1),
		-50
	);
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