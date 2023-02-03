#include "ToastNotification.h"
#include "Core/Managers/SettingsManager.h"
#include "Core/Systems/Logging.h"
#include "../Managers/EventManager.h"
#include "../Managers/ItemManager.h"
#include "../Player/Player.h"

#define RESET_TIMESTAMP -1.0f

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
ToastNotification::ToastNotification()
{
    ResetToastNotification();
}


// -------------------------------------------------------
// -------------------------------------------------------
ToastNotification::~ToastNotification()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void ToastNotification::Update()
{
    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Wrong Update method was called in ToastNotification.");
}


// -------------------------------------------------------
// -------------------------------------------------------
void ToastNotification::Update(float deltaTime)
{
    // Notification was just turned on. Needs initial timestamp.
    if (m_bShowNotification && m_fTimeStamp == RESET_TIMESTAMP)
    {
        m_fTimeStamp = deltaTime;
    }

    // Turn off the notification after m_fTimer amount of time.
    if (deltaTime > (m_fTimeStamp + m_fTimer))
    {
        m_bShowNotification = false;
        m_fTimeStamp = RESET_TIMESTAMP;
    }
}

// -------------------------------------------------------
// -------------------------------------------------------
void ToastNotification::Draw(SDL_Renderer* renderer)
{
    if (m_bShowNotification)
    {
        m_BackgroundBox.Draw(renderer);
        m_NotificationText.Draw(renderer);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void ToastNotification::Initialize()
{
    m_BackgroundBox.SetAnchor(HorizontalAlignment::eRight, VerticalAlignment::eTop);
    m_BackgroundBox.SetElementAlignment(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    m_BackgroundBox.SetSize(500, 75);
    m_BackgroundBox.SetColor(g_GameGlobals.COLOR_SILVER);
    m_BackgroundBox.SetOffset(25,25);

    m_NotificationText.SetAnchor(HorizontalAlignment::eRight, VerticalAlignment::eTop);
    m_NotificationText.SetElementAlignment(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    m_NotificationText.SetText("Notifaction Text.");
    m_NotificationText.SetColor(g_GameGlobals.COLOR_BLACK);
    m_NotificationText.SetOffset(CoreManagers::g_SettingsManager.GetRelativeScreenX(25), CoreManagers::g_SettingsManager.GetRelativeScreenX(50));


    g_EventManager.Subscribe(Events::eInventoryChanged, [this]() { ToastNotification::OnInventoryChangedEvent(); });
}


// -------------------------------------------------------
// -------------------------------------------------------
void ToastNotification::OnShow()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void ToastNotification::ResetToastNotification()
{
    m_bShowNotification = false;
    m_fTimeStamp = RESET_TIMESTAMP;
}


// -------------------------------------------------------
// -------------------------------------------------------
void ToastNotification::OnInventoryChangedEvent()
{
    const InventoryItemData& prevAddedInventoryItemData = g_Player.GetLastAddedInventoryItemData();
    uint32_t currItemIndex = g_ItemManager.m_ItemDataMap[prevAddedInventoryItemData.m_uiID];
    ItemData& currItem = g_ItemManager.m_ItemData[currItemIndex];

    if (currItem.m_Type == ItemType::eResource)
    {
        m_bShowNotification = true;

        std::string notificationText;
        notificationText.append(std::to_string(prevAddedInventoryItemData.m_uiAmount));
        notificationText.append(" ");
        notificationText.append(currItem.m_sName);
        notificationText.append(" added to inventory.");

        m_NotificationText.SetText(notificationText);
    }

    const int iTextLength = m_NotificationText.GetWidth();
    m_BackgroundBox.SetSize(iTextLength+25, m_BackgroundBox.GetHeight());

}

}