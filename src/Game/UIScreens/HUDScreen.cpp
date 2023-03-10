#include "HUDScreen.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/Systems/Systems.h"
#include "../Player/Player.h"
#include "../Managers/ItemManager.h"
#include "../Managers/EventManager.h"
#include "../Managers/GameplayManager.h"


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
#define STAMINA_POTION_ICON "txt_StaminaPotionIconUI"
#define STAMINA_ICON "txt_StaminaIconUI"
#define HEALTH_ICON  "txt_HealthIconUI"
#define DAY_ICON     "txt_DayIconUI"
#define NIGHT_ICON   "txt_NightIconUI"


namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
HUDScreen::HUDScreen()
    :  m_ArrowIcon(nullptr), m_StaminaPotionIcon(nullptr), m_AmmoAmountText(nullptr), m_StaminaPotionAmountText(nullptr)
{
}


// -------------------------------------------------------
// -------------------------------------------------------
HUDScreen::~HUDScreen()
{
    delete m_ArrowIcon;
    delete m_StaminaPotionIcon;
    delete m_AmmoAmountText;
    delete m_StaminaPotionAmountText;
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::Update()
{
    UpdateStaminabarUI();

    m_TimeText.SetText(g_GameplayManager.GetDisplayTime());


    // Only draw Skip to Night button during the daytime.
    if (g_GameplayManager.GetDayNightValue() == DayNightValues::eDay)
    {
        m_SkipNightButton.Update(CoreManagers::g_InputManager);
        if (m_SkipNightButton.LeftClickPressed())
        {
            g_GameplayManager.SkipToNight();
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::Draw(SDL_Renderer* renderer)
{
    m_ResourceStack.Draw(renderer);

    m_HealthIcon.Draw(renderer);
    m_HealthBarBackground.Draw(renderer);
    m_HealthBar.Draw(renderer);

    m_StaminaIcon.Draw(renderer);
    m_StaminaBarBackground.Draw(renderer);
    m_StaminaBar.Draw(renderer);

    if (g_ItemManager.GetPrimaryWeaponID() == CoreSystems::StringToHash32(std::string(HAMMER_ID)))
    {
        m_HammerIcon.Draw(renderer);
    }
    else
    {
        m_BowIcon.Draw(renderer);
    }

    m_AmmoStack.Draw(renderer);

    m_TimeText.Draw(renderer);
    m_DayCountText.Draw(renderer);


    // Only draw Skip to Night button during the daytime.
    if (g_GameplayManager.GetDayNightValue() == DayNightValues::eDay)
    {
        m_SkipNightButton.Draw(renderer);

        m_DayIcon.Draw(renderer);

    }
    else
    {
        m_NightIcon.Draw(renderer);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::Initialize()
{
    // Top Left Corner.
    m_HealthIcon.SetAnchor(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    m_HealthIcon.SetOffset(10, 10);
    m_HealthIcon.SetSize(25,25);
    m_HealthIcon.SetTexture(CoreSystems::StringToHash32(std::string(HEALTH_ICON)));

    m_HealthBarBackground.SetAnchor(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    m_HealthBarBackground.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(50), CoreManagers::g_SettingsManager.GetRelativeScreenY(10));
    m_HealthBarBackground.SetSize(200,25);
    m_HealthBarBackground.SetColor(g_GameGlobals.COLOR_BLACK);

    m_HealthBar.SetAnchor(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    m_HealthBar.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(52), CoreManagers::g_SettingsManager.GetRelativeScreenY(12));
    m_HealthBar.SetSize(196,21);
    m_HealthBar.SetColor(g_GameGlobals.COLOR_RED);
    
    OnPlayerHealthChangedEvent();

    m_StaminaIcon.SetAnchor(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    m_StaminaIcon.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(10), CoreManagers::g_SettingsManager.GetRelativeScreenY(50));
    m_StaminaIcon.SetSize(25,25);
    m_StaminaIcon.SetTexture(CoreSystems::StringToHash32(std::string(STAMINA_ICON)));

    m_StaminaBarBackground.SetAnchor(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    m_StaminaBarBackground.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(50), CoreManagers::g_SettingsManager.GetRelativeScreenY(50));
    m_StaminaBarBackground.SetSize(200,25);
    m_StaminaBarBackground.SetColor(g_GameGlobals.COLOR_BLACK);

    m_StaminaBar.SetAnchor(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    m_StaminaBar.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(52), CoreManagers::g_SettingsManager.GetRelativeScreenY(52));
    m_StaminaBar.SetSize(196,21);
    m_StaminaBar.SetColor(g_GameGlobals.COLOR_GREEN);

    m_HammerIcon.SetAnchor(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    m_HammerIcon.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(10), CoreManagers::g_SettingsManager.GetRelativeScreenY(90));
    m_HammerIcon.SetSize(25,25);
    m_HammerIcon.SetTexture(CoreSystems::StringToHash32(std::string(HAMMER_ICON)));

    m_BowIcon.SetAnchor(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    m_BowIcon.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(10), CoreManagers::g_SettingsManager.GetRelativeScreenY(90));
    m_BowIcon.SetSize(25,25);
    m_BowIcon.SetTexture(CoreSystems::StringToHash32(std::string(BOW_ICON)));

    OnPlayerEquippedItemChangedEvent();



    // Bottom Right Corner.
    m_ArrowIcon = new Icon(CoreSystems::StringToHash32(std::string(ARROW_ICON)));
    m_ArrowIcon->SetSize(25,25);

    m_AmmoAmountText = new TextBlock;
    m_AmmoAmountText->SetColor(g_GameGlobals.COLOR_WHITE);

    StackPanel* arrowStack = new StackPanel;
    arrowStack->SetChildAlignment(StackpanelAlignment::eHorizontal);
    arrowStack->SetElementAlignment(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    arrowStack->SetPadding(10);
    arrowStack->AddChild(m_ArrowIcon);
    arrowStack->AddChild(m_AmmoAmountText);
    
    m_StaminaPotionIcon = new Icon(CoreSystems::StringToHash32(std::string(STAMINA_POTION_ICON)));
    m_StaminaPotionIcon->SetSize(25,25);

    m_StaminaPotionAmountText = new TextBlock;
    m_StaminaPotionAmountText->SetColor(g_GameGlobals.COLOR_WHITE);

    StackPanel* staminaStack = new StackPanel;
    staminaStack->SetChildAlignment(StackpanelAlignment::eHorizontal);
    staminaStack->SetElementAlignment(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    staminaStack->SetPadding(10);
    staminaStack->AddChild(m_StaminaPotionIcon);
    staminaStack->AddChild(m_StaminaPotionAmountText);
    
    m_AmmoStack.SetAnchor(HorizontalAlignment::eRight, VerticalAlignment::eBottom);
    m_AmmoStack.SetChildAlignment(StackpanelAlignment::eVertical);
    m_AmmoStack.SetElementAlignment(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    m_AmmoStack.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(0), CoreManagers::g_SettingsManager.GetRelativeScreenY(-75));
    m_AmmoStack.SetPadding(-50);
    m_AmmoStack.AddChild(arrowStack); 
    m_AmmoStack.AddChild(staminaStack);

    OnAmmoCountChangedEvent();
    OnStaminaPotionUsedEvent();



    // Bottom Center.
    m_ScrapIcon.SetTexture(CoreSystems::StringToHash32(std::string(SCRAP_ICON)));
    m_ScrapIcon.SetSize(25,25);
    
    m_WoodIcon.SetTexture(CoreSystems::StringToHash32(std::string(WOOD_ICON)));
    m_WoodIcon.SetSize(25,25);
    
    m_WaterIcon.SetTexture(CoreSystems::StringToHash32(std::string(WATER_ICON)));
    m_WaterIcon.SetSize(25,25);
    
    m_ScrapAmountText.SetText("Scrap");
    m_ScrapAmountText.SetColor(g_GameGlobals.COLOR_WHITE);

    m_WoodAmountText.SetText("Wood");
    m_WoodAmountText.SetColor(g_GameGlobals.COLOR_WHITE);

    m_WaterAmountText.SetText("Water");
    m_WaterAmountText.SetColor(g_GameGlobals.COLOR_WHITE);

    m_ResourceStack.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eBottom);
    m_ResourceStack.SetChildAlignment(StackpanelAlignment::eHorizontal);
    m_ResourceStack.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_ResourceStack.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(0), CoreManagers::g_SettingsManager.GetRelativeScreenY(50));
    m_ResourceStack.SetPadding(15);
    m_ResourceStack.AddChild(&m_ScrapIcon);
    m_ResourceStack.AddChild(&m_ScrapAmountText);
    m_ResourceStack.AddChild(&m_WoodIcon);
    m_ResourceStack.AddChild(&m_WoodAmountText);
    m_ResourceStack.AddChild(&m_WaterIcon);
    m_ResourceStack.AddChild(&m_WaterAmountText);

    UpdateResourcesUI();



    // Top Center.
    m_DayIcon.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_DayIcon.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(-75), CoreManagers::g_SettingsManager.GetRelativeScreenY(25));
    m_DayIcon.SetSize(25,25);
    m_DayIcon.SetTexture(CoreSystems::StringToHash32(std::string(DAY_ICON)));

    m_NightIcon.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_NightIcon.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(-75), CoreManagers::g_SettingsManager.GetRelativeScreenY(25));
    m_NightIcon.SetSize(25,25);
    m_NightIcon.SetTexture(CoreSystems::StringToHash32(std::string(NIGHT_ICON)));

    m_DayCountText.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_DayCountText.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(-40), CoreManagers::g_SettingsManager.GetRelativeScreenY(25));
    m_DayCountText.SetText("Day Count");
    m_DayCountText.SetColor(g_GameGlobals.COLOR_WHITE);

    m_TimeText.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_TimeText.SetOffset(0, CoreManagers::g_SettingsManager.GetRelativeScreenX(25));
    m_TimeText.SetText("Time");
    m_TimeText.SetColor(g_GameGlobals.COLOR_WHITE);

    OnDayCountChangedEvent();


    m_SkipNightButton.SetAnchor(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_SkipNightButton.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(90), CoreManagers::g_SettingsManager.GetRelativeScreenY(25));
    m_SkipNightButton.SetText(" >>");
    m_SkipNightButton.SetSize(60,25);


    g_EventManager.Subscribe(Events::eInventoryChanged, [this]() { HUDScreen::OnInventoryChangedEvent(); });
    g_EventManager.Subscribe(Events::ePlayerHealthChanged, [this]() { HUDScreen::OnPlayerHealthChangedEvent(); });
    g_EventManager.Subscribe(Events::ePlayerPrimaryEquippedItemChanged, [this]() { HUDScreen::OnPlayerEquippedItemChangedEvent(); });
    g_EventManager.Subscribe(Events::eDayCountChanged, [this]() { HUDScreen::OnDayCountChangedEvent(); });
    g_EventManager.Subscribe(Events::eAmmoChanged, [this]() { HUDScreen::OnAmmoCountChangedEvent(); });
    g_EventManager.Subscribe(Events::eStaminaPotionUsed, [this]() { HUDScreen::OnStaminaPotionUsedEvent(); });

}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::OnShow()
{

}

// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::UpdateResourcesUI()
{
    const uint32_t uiScrapID = CoreSystems::StringToHash32(std::string(SCRAP_ID));
    const uint32_t uiWoodID = CoreSystems::StringToHash32(std::string(WOOD_ID));

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
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::UpdateHealthbarUI()
{
    float ihealthPercentage = static_cast<float>(g_Player.m_PlayerStatistics.GetCurrHealth()) / static_cast<float>(g_Player.m_PlayerStatistics.GetMaxHealth());
    float iHealthbarWidth = ihealthPercentage * m_uiBarMaxWidth;

    m_HealthBar.SetSize(static_cast<int>(iHealthbarWidth), m_uiBarMaxHeight);
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::UpdateStaminabarUI()
{
    float iStaminaPercentage = static_cast<float>(g_Player.m_PlayerStatistics.GetCurrStamina()) / static_cast<float>(g_Player.m_PlayerStatistics.GetMaxStamina());
    float iStaminaBarWidth = iStaminaPercentage * m_uiBarMaxWidth;

    m_StaminaBar.SetSize(static_cast<int>(iStaminaBarWidth), m_uiBarMaxHeight);
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::OnInventoryChangedEvent()
{
    UpdateResourcesUI();
    OnStaminaPotionUsedEvent();
    OnAmmoCountChangedEvent();
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::OnPlayerHealthChangedEvent()
{
    UpdateHealthbarUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::OnPlayerEquippedItemChangedEvent()
{
    m_bHammerEquipped = (g_ItemManager.GetPrimaryWeaponID() == CoreSystems::StringToHash32(std::string(HAMMER_ID)));
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::OnDayCountChangedEvent()
{
    m_DayCountText.SetText(std::to_string(g_GameplayManager.GetDayCount() + 1));
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::OnAmmoCountChangedEvent()
{
    uint32_t ammoID = CoreSystems::StringToHash32(std::string(AMMO_ID));
    const ItemData& ammoItemData = g_ItemManager.GetItemDataByID(ammoID);
 
    m_AmmoAmountText->SetText(std::to_string(ammoItemData.m_uiAmount));
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::OnStaminaPotionUsedEvent()
{
    uint32_t staminaPotionID = CoreSystems::StringToHash32(std::string(STAMINA_ICON));
    const ItemData& staminaPotionItemData = g_ItemManager.GetItemDataByID(staminaPotionID);
 
    m_StaminaPotionAmountText->SetText(std::to_string(staminaPotionItemData.m_uiAmount));
}

}