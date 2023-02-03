#include "UIManager.h"

#include "MapManager.h"
#include "GameManager.h"
#include "EventManager.h"
#include "Core/Systems/Systems.h"


namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
UIManager g_UIManager;


// -------------------------------------------------------
// -------------------------------------------------------
UIManager::UIManager()
{
    m_ActiveScreen = ActiveScreen::eIntro;
}


// -------------------------------------------------------
// -------------------------------------------------------
UIManager::~UIManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::InitializeUIScreens()
{
    m_HUDScreen.Initialize();
    m_PauseScreen.Initialize();
    m_GameOverlayScreen.Initialize();
    m_DebugScreen.Initialize();
    m_CraftingScreen.Initialize();
    m_Notification.Initialize();
    m_GameOverScreen.Initialize();
    m_IntroScreen.Initialize();
    m_ControlsScreen.Initialize();

    g_EventManager.Subscribe(Events::eGameOverChanged, [this]() { UIManager::OnGameOverChanged(); });
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::Update(float deltaTime)
{
    switch (m_ActiveScreen)
    {
    case ActiveScreen::eHud:
    {
        m_GameOverlayScreen.Update();
        m_HUDScreen.Update();
        break;
    }
    case ActiveScreen::eInventory:
    {
        m_CraftingScreen.Update();
        m_HUDScreen.Update();
        break;
    }
    case ActiveScreen::ePause:
    {
        m_PauseScreen.Update();
        break;
    }
    case ActiveScreen::eGameOver:
    {
        m_GameOverScreen.Update();
        break;
    }
    case ActiveScreen::eIntro:
    {
        m_IntroScreen.Update();
        break;
    }
    case ActiveScreen::eControls:
    {
        m_ControlsScreen.Update();
        break;
    }
    default: 
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "UI Update corrupted.");
        break;
    }
    }

    m_Notification.Update(deltaTime);

    if (g_GameManager.DebugScreenActive())
    {
        m_DebugScreen.Update();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::Draw(SDL_Renderer* renderer)
{
    switch (m_ActiveScreen)
    {
    case ActiveScreen::eHud:
    {
        m_GameOverlayScreen.Draw(renderer);
        m_HUDScreen.Draw(renderer);
        break;
    }
    case ActiveScreen::eInventory:
    {
        m_CraftingScreen.Draw(renderer);
        break;
    }
    case ActiveScreen::ePause:
    {
        m_PauseScreen.Draw(renderer);
        break;
    }
    case ActiveScreen::eGameOver:
    {
        m_GameOverScreen.Draw(renderer);
        break;
    }
    case ActiveScreen::eIntro:
    {
        m_IntroScreen.Draw(renderer);
        break;
    }
    case ActiveScreen::eControls:
    {
        m_ControlsScreen.Draw(renderer);
        break;
    }
    default:
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "UI Draw corrupted.");
        break;
    }
    }

    m_Notification.Draw(renderer);

    if (g_GameManager.DebugScreenActive())
    {
        m_DebugScreen.Draw(renderer);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::ActivatePauseMenu()
{
    if (m_ActiveScreen == ActiveScreen::ePause)
    {
        m_ActiveScreen = ActiveScreen::eHud;
        g_GameManager.SetGameIsPaused(false);
        return;
    }

    m_ActiveScreen = ActiveScreen::ePause;
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::ActivateInventoryMenu()
{
    if (m_ActiveScreen == ActiveScreen::eInventory)
    {
        m_ActiveScreen = ActiveScreen::eHud;
        g_GameManager.SetGameIsPaused(false);
    }
    else
    {
        m_ActiveScreen = ActiveScreen::eInventory;
        m_CraftingScreen.OnShow();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::ActivateControlsScreen()
{
    if (m_ActiveScreen == ActiveScreen::eControls)
    {
        if (!g_GameManager.IntroSeen())
        {
            m_ActiveScreen = ActiveScreen::eIntro;
        }
        else
        {
            m_ActiveScreen = ActiveScreen::ePause;
        }
    }
    else
    {
        m_ActiveScreen = ActiveScreen::eControls;
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::AddNewRefreshUI(uint32_t uiMapIDHash, int iPositionX, int iPositionY)
{
    RefreshUI newRefreshUI;
    newRefreshUI.m_uiMapIDHash = uiMapIDHash;
    newRefreshUI.m_bActive = true;
    newRefreshUI.m_RefreshText.SetElementAlignment(HorizontalAlignment::eLeft, VerticalAlignment::eTop);
    newRefreshUI.m_RefreshText.SetPosition(iPositionX, iPositionY);
    newRefreshUI.m_RefreshText.SetText("0");
    newRefreshUI.m_RefreshText.SetColor(g_GameGlobals.COLOR_WHITE);


    if (m_GameOverlayScreen.m_RefreshTextMap.find(uiMapIDHash) != m_GameOverlayScreen.m_RefreshTextMap.end())
    {
        std::vector<RefreshUI>& refreshUIVector = m_GameOverlayScreen.m_RefreshTextMap[uiMapIDHash];
        refreshUIVector.push_back(newRefreshUI);
    }
    else
    {
        std::vector<RefreshUI> newRefreshVector;
        newRefreshVector.push_back(newRefreshUI);
        m_GameOverlayScreen.m_RefreshTextMap.insert({ uiMapIDHash, newRefreshVector });
    }

}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::UpdatePickupUI(bool bShow, uint16_t uiCount, int x, int y)
{
    m_GameOverlayScreen.m_bShowCooldownUI = bShow;

    if (m_GameOverlayScreen.m_bShowCooldownUI)
    {
        m_GameOverlayScreen.m_PickupCooldownText.SetText(std::to_string(uiCount));

        m_GameOverlayScreen.m_PickupCooldownText.SetPosition(x, y);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::UpdateRefreshUI(bool bShow, uint16_t uiIndex, uint16_t uiCount)
{
    std::vector<RefreshUI>& refreshUIVector = m_GameOverlayScreen.m_RefreshTextMap[g_MapManager.m_ActiveMap->m_uiIDHash];
    if (uiIndex < refreshUIVector.size())
    {
        RefreshUI& currRefresh = refreshUIVector[uiIndex];

        currRefresh.m_bActive = bShow;

        currRefresh.m_RefreshText.SetText(std::to_string(uiCount));
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::ResetUIManager()
{
    m_Notification.ResetToastNotification();

    if (!g_GameManager.IntroSeen())
    {
        m_ActiveScreen = ActiveScreen::eIntro;
    }
    else
    {
        m_ActiveScreen = ActiveScreen::eHud;
    }

    g_EventManager.Broadcast(Events::ePlayerHealthChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::OnGameOverChanged()
{
    if (g_GameManager.IsGameOver())
    {
        m_ActiveScreen = ActiveScreen::eGameOver;
        m_GameOverScreen.SetGameOverMessage(g_GameManager.GetEndGameOverMessageText());
    }
}

}