#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "ActionBase.h"
#include "Core/Types/Sprite.h"

namespace Florida
{

class MeleeAction : public ActionBase
{
public:
    MeleeAction();
    ~MeleeAction();

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);

    void SetPosition(int x, int y) {};
    void SetDirection(Direction direction);

    void SetInitialTime(float fInitialTime);


private:

    void SetPosition();


private:

    Core::Sprite* m_SpriteHorizontal;
    Core::Sprite* m_SpriteVertical;

    const int m_iOffset = 2;

    const uint8_t m_uiStaminaUseAmount = 20;

    const float m_fMeleeTimer = 0.25f;
    float m_fMeleeTimeStamp = 0.0f;

};

}