#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "Core/UI/UIScreenBase.h"
#include "Core/UI/Types/Box.h"
#include "Core/UI/Types/TextBlock.h"

using namespace UI;

namespace Florida
{

class ToastNotification : public UIScreenBase
{
public:
    ToastNotification();
    ~ToastNotification();

    void Initialize() override;

    void Update() override;
    void Update(float deltaTime);

    void Draw(SDL_Renderer* renderer) override;

    void OnShow() override;
    void RemoveSelf() override;

    void ResetToastNotification();


private:

    void OnInventoryChangedEvent();


private:
   
    bool m_bShowNotification;

    const float m_fTimer = 3.0f; // 1 second.
    float m_fTimeStamp = 0.0f;

    TextBlock m_NotificationText;

};
}