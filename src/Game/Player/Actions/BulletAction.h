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

    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);

    void SetPosition(int x, int y);
    void SetDirection(Direction direction);


private:

    void UpdateBulletPosition();


private:

    CoreTypes::Sprite* m_SpriteVertical;
    CoreTypes::Sprite* m_SpriteHorizontal;
    
    const uint8_t m_uiSpeed = 5;

};

}