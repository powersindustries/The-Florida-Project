#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "../UIScreens/HUDScreen.h"
#include "../UIScreens/PauseScreen.h"
#include "../UIScreens/GameOverlayScreen.h"
#include "../UIScreens/DebugScreen.h"
#include "../UIScreens/ToastNotification.h"
#include "../UIScreens/CraftingScreen.h"
#include "../UIScreens/GameOverScreen.h"
#include "../UIScreens/IntroScreen.h"
#include "../UIScreens/ControlsScreen.h"

namespace Florida
{


enum class ActiveScreen
{
    eHud,
    eInventory,
    ePause,
    eGameOver,
    eIntro,
    eControls
};


class UIManager
{
public:
    UIManager();
    ~UIManager();

    void InitializeUIScreens();

    void Update(float* deltaTime);
    void Draw(SDL_Renderer* renderer);

    void ActivatePauseMenu();
    void ActivateInventoryMenu();
    void ActivateControlsScreen();

    void AddNewRefreshUI(uint32_t uiMapIDHash, int iPositionX, int iPositionY);

    void UpdatePickupUI(bool bShow, uint16_t uiCount, int x, int y);
    void UpdateRefreshUI(bool bShow, uint16_t uiIndex, uint16_t uiCount);

    void ResetUIManager();


private:

    void OnGameOverChanged();


private:

    ActiveScreen m_ActiveScreen;

    HUDScreen m_HUDScreen;
    PauseScreen m_PauseScreen;
    GameOverlayScreen m_GameOverlayScreen;
    DebugScreen m_DebugScreen;
    CraftingScreen m_CraftingScreen;
    ToastNotification m_Notification;
    GameOverScreen m_GameOverScreen;
    IntroScreen m_IntroScreen;
    ControlsScreen m_ControlsScreen;

};

extern UIManager g_UIManager;
}