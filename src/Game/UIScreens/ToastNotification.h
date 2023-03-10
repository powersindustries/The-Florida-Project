#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/TextBlock.h"

using namespace CoreUI;

namespace Florida
{

class ToastNotification : public UIScreenBase
{
public:
    ToastNotification();
    ~ToastNotification();

    void Update();
    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);
    void Initialize();
    void OnShow();

    void ResetToastNotification();


private:

    void OnInventoryChangedEvent();


private:
   
    bool m_bShowNotification;

    const float m_fTimer = 3.0f; // 1 second.
    float m_fTimeStamp = 0.0f;

    Box m_BackgroundBox;
    TextBlock m_NotificationText;

};
}