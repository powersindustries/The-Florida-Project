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
{
}


// -------------------------------------------------------
// -------------------------------------------------------
HUDScreen::~HUDScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::Update()
{
    UpdateStaminabarUI();

    m_TimeText.SetText(g_GameplayManager.GetDisplayTime());
    m_TimeText.SetOffset(
        ( (m_TimeText.GetWidth() / 2) * -1),
        m_DayNightStack.GetHeight() + 20
    );

    // Only draw Skip to Night button during the daytime.
    if (g_GameplayManager.GetDayNightValue() == DayNightValues::eDay)
    {
        m_SkipNightButton.Update();
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
    m_IconStack.Draw(renderer);
    m_BarBackgroundStack.Draw(renderer);
    m_BarStack.Draw(renderer);
    m_AmmoStack.Draw(renderer);
    m_StaminaPotionStack.Draw(renderer);
    m_ResourceStack.Draw(renderer);
    m_DayNightStack.Draw(renderer);
    m_TimeText.Draw(renderer);

    // Only draw Skip to Night button during the daytime.
    if (g_GameplayManager.GetDayNightValue() == DayNightValues::eDay)
    {
        m_SkipNightButton.Draw(renderer);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::Initialize()
{
    // Top Left Corner.
    m_HealthIcon.SetTexture(Core::StringToHash32(std::string(HEALTH_ICON)));
    m_HealthIcon.SetSize(25,25);

	m_StaminaIcon.SetTexture(Core::StringToHash32(std::string(STAMINA_ICON)));
	m_StaminaIcon.SetSize(25, 25);

	m_WeaponIcon.SetTexture(Core::StringToHash32(std::string(HAMMER_ICON)));
	m_WeaponIcon.SetSize(25, 25);

	m_IconStack.SetAnchor(Anchor::eTopLeft);
    m_IconStack.SetPadding(10);
    m_IconStack.AddChild(&m_HealthIcon);
    m_IconStack.AddChild(&m_StaminaIcon);
    m_IconStack.AddChild(&m_WeaponIcon);
    m_IconStack.SetOffset(10,10);

	m_HealthBarBackground.SetColor(g_GameGlobals.COLOR_BLACK);
	m_HealthBarBackground.SetSize(200, 25);

	m_StaminaBarBackground.SetColor(g_GameGlobals.COLOR_BLACK);
	m_StaminaBarBackground.SetSize(200, 25);

	m_BarBackgroundStack.SetAnchor(Anchor::eTopLeft);
	m_BarBackgroundStack.SetPadding(10);
	m_BarBackgroundStack.AddChild(&m_HealthBarBackground);
	m_BarBackgroundStack.AddChild(&m_StaminaBarBackground);
	m_BarBackgroundStack.SetOffset(
		m_IconStack.GetWidth() + 25,
		10
	);

	m_HealthBar.SetColor(g_GameGlobals.COLOR_RED);
	m_HealthBar.SetSize(m_uiBarMaxWidth, m_uiBarMaxHeight);

	m_StaminaBar.SetColor(g_GameGlobals.COLOR_GREEN);
	m_StaminaBar.SetSize(m_uiBarMaxWidth, m_uiBarMaxHeight);

	m_BarStack.SetAnchor(Anchor::eTopLeft);
	m_BarStack.SetPadding(14);
	m_BarStack.AddChild(&m_HealthBar);
	m_BarStack.AddChild(&m_StaminaBar);
	m_BarStack.SetOffset(
		m_IconStack.GetWidth() + 27,
		12
    );

    OnPlayerHealthChangedEvent();
    OnPlayerEquippedItemChangedEvent();


    // Bottom Right Corner.
    m_StaminaPotionIcon.SetTexture(Core::StringToHash32(std::string(STAMINA_POTION_ICON)));
    m_StaminaPotionIcon.SetSize(25,25);

    m_StaminaPotionAmountText.SetColor(g_GameGlobals.COLOR_WHITE);
    m_StaminaPotionAmountText.SetText("N");

    m_StaminaPotionStack.SetAnchor(Anchor::eBottomLeft);
    m_StaminaPotionStack.SetPadding(10);
    m_StaminaPotionStack.AddChild(&m_StaminaPotionIcon);
    m_StaminaPotionStack.AddChild(&m_StaminaPotionAmountText);
    m_StaminaPotionStack.SetOffset(
        10,
        -10
    );

    m_AmmoIcon.SetTexture(Core::StringToHash32(std::string(ARROW_ICON)));
    m_AmmoIcon.SetSize(25,25);

    m_AmmoAmountText.SetColor(g_GameGlobals.COLOR_WHITE);
    m_AmmoAmountText.SetText("N");

	m_AmmoStack.SetAnchor(Anchor::eBottomLeft);
	m_AmmoStack.SetPadding(10);
	m_AmmoStack.AddChild(&m_AmmoIcon);
	m_AmmoStack.AddChild(&m_AmmoAmountText);
	m_AmmoStack.SetOffset(
        10,
        (m_StaminaPotionStack.GetHeight() * -1) - 20
	);

    OnAmmoCountChangedEvent();
    OnStaminaPotionUsedEvent();


    // Bottom Center.
    m_ScrapIcon.SetTexture(Core::StringToHash32(std::string(SCRAP_ICON)));
    m_ScrapIcon.SetSize(25,25);
    
    m_WoodIcon.SetTexture(Core::StringToHash32(std::string(WOOD_ICON)));
    m_WoodIcon.SetSize(25,25);
    
    m_WaterIcon.SetTexture(Core::StringToHash32(std::string(WATER_ICON)));
    m_WaterIcon.SetSize(25,25);
 
    m_ScrapAmountText.SetColor(g_GameGlobals.COLOR_WHITE);
    m_ScrapAmountText.SetText("Scrap");

    m_WoodAmountText.SetColor(g_GameGlobals.COLOR_WHITE);
    m_WoodAmountText.SetText("Wood");

    m_WaterAmountText.SetColor(g_GameGlobals.COLOR_WHITE);
    m_WaterAmountText.SetText("Water");

    m_ResourceStack.SetAnchor(Anchor::eBottomCenter);
    m_ResourceStack.SetPadding(15);
    m_ResourceStack.AddChild(&m_ScrapIcon);
    m_ResourceStack.AddChild(&m_ScrapAmountText);
    m_ResourceStack.AddChild(&m_WoodIcon);
    m_ResourceStack.AddChild(&m_WoodAmountText);
    m_ResourceStack.AddChild(&m_WaterIcon);
    m_ResourceStack.AddChild(&m_WaterAmountText);
    m_ResourceStack.SetOffset(
        ( (m_ResourceStack.GetWidth() / 2) * -1),
        -10 
    );

    UpdateResourcesUI();

    // Top Center.
    m_DayNightIcon.SetAnchor(Anchor::eTopCenter);
    m_DayNightIcon.SetTexture(Core::StringToHash32(std::string(DAY_ICON)));
    m_DayNightIcon.SetSize(25,25);

    m_DayCountText.SetAnchor(Anchor::eTopCenter);
    m_DayCountText.SetColor(g_GameGlobals.COLOR_WHITE);
    m_DayCountText.SetText("Day Count");

    m_DayNightStack.SetAnchor(Anchor::eTopCenter);
    m_DayNightStack.SetPadding(25);
    m_DayNightStack.AddChild(&m_DayNightIcon);
    m_DayNightStack.AddChild(&m_DayCountText);
    m_DayNightStack.SetOffset(
        ( (m_DayNightStack.GetWidth() / 2) * -1),
        10 
    );

    OnDayCountChangedEvent();

    m_TimeText.SetAnchor(Anchor::eTopCenter);
    m_TimeText.SetColor(g_GameGlobals.COLOR_WHITE);
    m_TimeText.SetText("Time");
    m_TimeText.SetOffset(
        ( (m_TimeText.GetWidth() / 2) * -1),
        m_TimeText.GetHeight() + 10
    );

    m_SkipNightButton.SetAnchor(Anchor::eTopCenter);
    m_SkipNightButton.SetText("SKIP");
    m_SkipNightButton.SetSize(200, 50);
    m_SkipNightButton.SetOffset(
        ( (m_SkipNightButton.GetWidth() / 2) * -1),
        75 
    );


    g_EventManager.Subscribe(Events::eInventoryChanged, [this]() { HUDScreen::OnInventoryChangedEvent(); });
    g_EventManager.Subscribe(Events::ePlayerHealthChanged, [this]() { HUDScreen::OnPlayerHealthChangedEvent(); });
    g_EventManager.Subscribe(Events::ePlayerPrimaryEquippedItemChanged, [this]() { HUDScreen::OnPlayerEquippedItemChangedEvent(); });
    g_EventManager.Subscribe(Events::eDayCountChanged, [this]() { HUDScreen::OnDayCountChangedEvent(); });
    g_EventManager.Subscribe(Events::eAmmoChanged, [this]() { HUDScreen::OnAmmoCountChangedEvent(); });
    g_EventManager.Subscribe(Events::eStaminaPotionUsed, [this]() { HUDScreen::OnStaminaPotionUsedEvent(); });
    g_EventManager.Subscribe(Events::eDayNightChanged, [this]() { HUDScreen::OnDayNightChangedEvent(); });

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

    // Recenter Resources Stack after updating text.
    m_ResourceStack.SetOffset(
        ( (m_ResourceStack.GetWidth() / 2) * -1),
        -10 
    );
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::UpdateHealthbarUI()
{
    float ihealthPercentage = static_cast<float>(g_Player.m_PlayerStatistics.GetCurrHealth()) / static_cast<float>(g_Player.m_PlayerStatistics.GetMaxHealth());
    float iHealthbarWidth = ihealthPercentage * m_uiBarMaxWidth;

    m_HealthBar.SetSize(static_cast<int>(iHealthbarWidth), m_uiBarMaxHeight);

    m_BarStack.RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::UpdateStaminabarUI()
{
    float iStaminaPercentage = static_cast<float>(g_Player.m_PlayerStatistics.GetCurrStamina()) / static_cast<float>(g_Player.m_PlayerStatistics.GetMaxStamina());
    float iStaminaBarWidth = iStaminaPercentage * m_uiBarMaxWidth;

    m_StaminaBar.SetSize(static_cast<int>(iStaminaBarWidth), m_uiBarMaxHeight);

    m_BarStack.RefreshUI();
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
    if (g_ItemManager.GetPrimaryWeaponID() == Core::StringToHash32(std::string(HAMMER_ID)))
    {
        m_WeaponIcon.SetTexture(Core::StringToHash32(std::string(HAMMER_ICON)));
    }
    else
    {
        m_WeaponIcon.SetTexture(Core::StringToHash32(std::string(BOW_ICON)));
    }

    m_IconStack.RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::OnDayCountChangedEvent()
{
    m_DayCountText.SetText(std::to_string(g_GameplayManager.GetDayCount() + 1));

    m_DayNightStack.RefreshUI();

    m_DayNightStack.SetOffset(
        ( (m_DayNightStack.GetWidth() / 2) * -1),
        10
    );

}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::OnAmmoCountChangedEvent()
{
    uint32_t ammoID = Core::StringToHash32(std::string(AMMO_ID));
    const ItemData& ammoItemData = g_ItemManager.GetItemDataByID(ammoID);
 
    m_AmmoAmountText.SetText(std::to_string(ammoItemData.m_uiAmount));

    m_AmmoStack.RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::OnStaminaPotionUsedEvent()
{
    uint32_t staminaPotionID = Core::StringToHash32(std::string(STAMINA_ICON));
    const ItemData& staminaPotionItemData = g_ItemManager.GetItemDataByID(staminaPotionID);
 
    m_StaminaPotionAmountText.SetText(std::to_string(staminaPotionItemData.m_uiAmount));

    m_StaminaPotionStack.RefreshUI();
}


// -------------------------------------------------------
// -------------------------------------------------------
void HUDScreen::OnDayNightChangedEvent()
{
	if (g_GameplayManager.GetDayNightValue() == DayNightValues::eDay)
	{
        m_DayNightIcon.SetTexture(Core::StringToHash32(std::string(DAY_ICON)));
	}
    else
    {
        m_DayNightIcon.SetTexture(Core::StringToHash32(std::string(NIGHT_ICON)));
    }

    m_DayNightStack.RefreshUI();
	m_DayNightStack.SetOffset(
		((m_DayNightStack.GetWidth() / 2) * -1),
		10
	);
}

}