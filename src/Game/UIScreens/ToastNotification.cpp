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
    Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Wrong Update method was called in ToastNotification.");
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
        m_NotificationText.Draw(renderer);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void ToastNotification::Initialize()
{
    m_NotificationText.SetAnchor(Anchor::eTopRight);
    m_NotificationText.SetColor(g_GameGlobals.COLOR_WHITE);
    m_NotificationText.SetText("Notifaction Text.");
    m_NotificationText.SetOffset(
        Core::g_SettingsManager.GetRelativeScreenX(-25), 
        Core::g_SettingsManager.GetRelativeScreenY(50)
    );


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
    const ItemData& lastAddedItem = g_ItemManager.GetLastAddedItemData();

    if (lastAddedItem.m_Type == ItemType::eResource)
    {
        m_bShowNotification = true;

        std::string notificationText;
        notificationText.append(std::to_string(lastAddedItem.m_uiAmount));
        notificationText.append(" ");
        notificationText.append(lastAddedItem.m_sName);
        notificationText.append(" added to inventory.");

        m_NotificationText.SetText(notificationText);
    }

    const int iTextLength = m_NotificationText.GetWidth();
}

}