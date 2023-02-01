#include "GameOverlayScreen.h"

#include "Core/Systems/Systems.h"
#include "Core/Managers/SettingsManager.h"
#include "../Managers/MapManager.h"


namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
GameOverlayScreen::GameOverlayScreen()
{
    m_bShowCooldownUI = false;
}


// -------------------------------------------------------
// -------------------------------------------------------
GameOverlayScreen::~GameOverlayScreen()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameOverlayScreen::Update()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameOverlayScreen::Draw(SDL_Renderer* renderer)
{
    if (m_bShowCooldownUI)
    {
        m_PickupCooldownText.Draw(renderer);
    }

    std::vector<RefreshUI> refreshUIVector = m_RefreshTextMap[g_MapManager.m_ActiveMap->m_uiIDHash];
    const uint16_t uiRefreshSize = static_cast<uint16_t>(refreshUIVector.size());
    for (uint16_t x=0; x < uiRefreshSize; ++x)
    {
        RefreshUI& currRefreshUI = refreshUIVector[x];
        if (currRefreshUI.m_bActive)
        {
            currRefreshUI.m_RefreshText.Draw(renderer);
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameOverlayScreen::Initialize()
{
    m_PickupCooldownText.SetElementAlignment(HorizontalAlignment::eCenter, VerticalAlignment::eTop);
    m_PickupCooldownText.SetPosition(CoreManagers::g_SettingsManager.GetRelativeScreenX(200), CoreManagers::g_SettingsManager.GetRelativeScreenY(200));
    m_PickupCooldownText.SetText("Number");
    m_PickupCooldownText.SetColor(g_GameGlobals.COLOR_WHITE);
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameOverlayScreen::OnShow()
{

}

}
