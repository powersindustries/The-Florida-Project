#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image

#include "ActionBase.h"
#include "Core/Types/Sprite.h"

namespace Florida
{

class BulletAction : public ActionBase
{
public:
    BulletAction();
    ~BulletAction();

    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

    void SetPosition(int x, int y) override;
    void SetDirection(Direction direction) override;


private:

    void UpdateBulletPosition();


private:

    Core::Sprite* m_SpriteVertical;
    Core::Sprite* m_SpriteHorizontal;
    
    const uint8_t m_uiSpeed = 5;

};
}