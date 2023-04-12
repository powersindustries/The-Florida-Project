#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <stack>

#include "Core/UI/UIScreenBase.h"

#include "../UIScreens/HUDScreen.h"
#include "../UIScreens/PauseScreen.h"
#include "../UIScreens/GameOverlayScreen.h"
#include "../UIScreens/DebugScreen.h"
#include "../UIScreens/ToastNotification.h"
#include "../UIScreens/CraftingScreen.h"
#include "../UIScreens/GameOverScreen.h"
#include "../UIScreens/IntroScreen.h"
#include "../UIScreens/ControlsScreen.h"

using namespace UI;

namespace Florida
{

class UIManager
{
public:
    UIManager();
    ~UIManager();

    void Initialize();

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);

	const UIScreenID GetActiveScreenID();
	void ActivateScreen(UIScreenID screenID);

	void RemoveScreen(UIScreenID screenID);

    void AddNewRefreshUI(uint32_t uiMapIDHash, int iPositionX, int iPositionY);

    void UpdatePickupUI(bool bShow, uint16_t uiCount, int x, int y);
    void UpdateRefreshUI(bool bShow, uint16_t uiIndex, uint16_t uiCount);

    void ResetUIManager();


private:

	void CallOnShow();
    void OnGameOverChanged();


private:

    std::stack<UIScreenID> m_ScreenStack;

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