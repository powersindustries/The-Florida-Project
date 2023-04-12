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
void GameOverlayScreen::Initialize()
{
	m_PickupCooldownText.SetAnchor(Anchor::eTopLeft);
	m_PickupCooldownText.SetText("Number");
	m_PickupCooldownText.SetColor(g_GameGlobals.COLOR_WHITE);
	m_PickupCooldownText.SetOffset(200, 200);
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

    std::vector<RefreshUI> refreshUIVector = m_RefreshTextMap[g_MapManager.m_ActiveMap->m_uiID];
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
void GameOverlayScreen::OnShow()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameOverlayScreen::RemoveSelf()
{
}

}
