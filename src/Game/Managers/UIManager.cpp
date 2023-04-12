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
    m_ScreenStack.push(UIScreenID::eIntro);
}


// -------------------------------------------------------
// -------------------------------------------------------
UIManager::~UIManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::Initialize()
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
    switch (GetActiveScreenID())
    {
    case UIScreenID::eHud:
    {
        m_GameOverlayScreen.Update();
        m_HUDScreen.Update();
        break;
    }
    case UIScreenID::eInventory:
    {
        m_CraftingScreen.Update();
        m_HUDScreen.Update();
        break;
    }
    case UIScreenID::ePause:
    {
        m_PauseScreen.Update();
        break;
    }
    case UIScreenID::eGameOver:
    {
        m_GameOverScreen.Update();
        break;
    }
    case UIScreenID::eIntro:
    {
        m_IntroScreen.Update();
        break;
    }
    case UIScreenID::eControls:
    {
        m_ControlsScreen.Update();
        break;
    }
    default: 
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "UI Update corrupted.");
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
    switch (GetActiveScreenID())
    {
    case UIScreenID::eHud:
    {
        m_GameOverlayScreen.Draw(renderer);
        m_HUDScreen.Draw(renderer);
        break;
    }
    case UIScreenID::eInventory:
    {
        m_CraftingScreen.Draw(renderer);
        break;
    }
    case UIScreenID::ePause:
    {
        m_PauseScreen.Draw(renderer);
        break;
    }
    case UIScreenID::eGameOver:
    {
        m_GameOverScreen.Draw(renderer);
        break;
    }
    case UIScreenID::eIntro:
    {
        m_IntroScreen.Draw(renderer);
        break;
    }
    case UIScreenID::eControls:
    {
        m_ControlsScreen.Draw(renderer);
        break;
    }
    default:
    {
        Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "UI Draw corrupted.");
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
const UI::UIScreenID UIManager::GetActiveScreenID()
{
    return m_ScreenStack.top();
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::ActivateScreen(UIScreenID screenID)
{
	if (GetActiveScreenID() != screenID)
	{
		m_ScreenStack.push(screenID);
		CallOnShow();

        g_GameManager.SetGameIsPaused(GetActiveScreenID() != UIScreenID::eHud);
	}
	else
	{
		std::string errorMessage = "Youre attempting to activate a screen that is already active. Current active ScreenID: ";
		errorMessage.append(std::to_string(static_cast<int>(GetActiveScreenID())));

		Core::SYSTEMS_LOG(Core::LoggingLevel::eError, errorMessage);
	}
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::RemoveScreen(UIScreenID screenID)
{
	if (GetActiveScreenID() == screenID)
	{
		m_ScreenStack.pop();

        g_GameManager.SetGameIsPaused(GetActiveScreenID() != UIScreenID::eHud);
	}
	else
	{
		std::string errorMessage = "Screen youre removing is not current active screen. Current active ScreenID: ";
		errorMessage.append(std::to_string(static_cast<int>(GetActiveScreenID())));
		errorMessage.append(", input screenID: ");
		errorMessage.append(std::to_string(static_cast<int>(screenID)));

		Core::SYSTEMS_LOG(Core::LoggingLevel::eError, errorMessage);
	}
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::AddNewRefreshUI(uint32_t uiMapIDHash, int iPositionX, int iPositionY)
{
    RefreshUI newRefreshUI;
    newRefreshUI.m_uiMapIDHash = uiMapIDHash;
    newRefreshUI.m_bActive = true;
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
    std::vector<RefreshUI>& refreshUIVector = m_GameOverlayScreen.m_RefreshTextMap[g_MapManager.m_ActiveMap->m_uiID];
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

    // Clear Stack.
    const uint8_t uiStackSize = static_cast<uint8_t>(m_ScreenStack.size());
    for (uint8_t x=0; x < uiStackSize; ++x)
    {
        m_ScreenStack.pop();
    }

    if (!g_GameManager.IntroSeen())
    {
        m_ScreenStack.push(UIScreenID::eIntro);
    }
    else
    {
        m_ScreenStack.push(UIScreenID::eHud);
    }

    g_EventManager.Broadcast(Events::ePlayerHealthChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::CallOnShow()
{
	switch (GetActiveScreenID())
	{
	case UIScreenID::eHud:
	{
		m_HUDScreen.OnShow();
		break;
	}
	case UIScreenID::eInventory:
	{
		m_CraftingScreen.OnShow();
		break;
	}
	case UIScreenID::ePause:
	{
		m_PauseScreen.OnShow();
		break;
	}
	case UIScreenID::eGameOver:
	{
		m_GameOverScreen.OnShow();
		break;
	}
	case UIScreenID::eIntro:
	{
		m_IntroScreen.OnShow();
		break;
	}
	case UIScreenID::eControls:
	{
		m_ControlsScreen.OnShow();
		break;
	}
	default:
	{
		Core::SYSTEMS_LOG(Core::LoggingLevel::eError, "UI Draw corrupted.");
		break;
	}
	}

}


// -------------------------------------------------------
// -------------------------------------------------------
void UIManager::OnGameOverChanged()
{
    if (g_GameManager.IsGameOver())
    {
        //m_ActiveScreen = ActiveScreen::eGameOver;
        ActivateScreen(UIScreenID::eGameOver);
        m_GameOverScreen.SetGameOverMessage(g_GameManager.GetEndGameOverMessageText());
    }
}

}