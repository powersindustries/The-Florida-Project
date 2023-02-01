#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <map>

#include "Transform.h"
#include "String.h"

namespace CoreTypes
{


enum class SpriteType
{
    eAnimanted,
    eNonAnimated
};


class AnimationData
{
public:
    AnimationData() : m_uiIndex(0), m_uiFrameCount(0), m_uiAnimationSpeed(0) {};
    ~AnimationData() {};

    AnimationData(unsigned int index, unsigned int frameCount, unsigned int animationSpeed)
    {
        m_uiIndex = index;
        m_uiFrameCount = frameCount;
        m_uiAnimationSpeed = animationSpeed;
    }

    unsigned int m_uiIndex;
    unsigned int m_uiFrameCount;
    unsigned int m_uiAnimationSpeed;
};


class Sprite
{
public:
    Sprite();
    ~Sprite();

    // Non-Animated Texture constructor
    Sprite(uint32_t assetIDHash, SpriteType spriteType = SpriteType::eNonAnimated);
    // Animated Texture constructor
    Sprite(uint32_t assetIDHash, uint8_t animationSpeed, SpriteType spriteType = SpriteType::eAnimanted);

    void Update(float deltaTime);
    void Update(float deltaTime, SDL_Rect& inRectangle);
    void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void SetTexture(uint32_t textureIDHash);

    void SetRotation(double degrees);

    void SetPosition(SDL_Rect inRectangle);

    inline const int GetWidth() { return m_Transform.m_iWidth; }
    inline const int GetHeight() { return m_Transform.m_iHeight; }


private:

    SDL_Texture* m_Texture;

    SDL_Rect m_SourceRectangle;
    SDL_Rect m_DestinationRectangle;

    Transform m_Transform;

    SpriteType m_SpriteType;
    uint8_t m_uiFrameNumber;
    uint8_t m_uiAnimationSpeed;

    // In Degrees, Clockwise
    double m_dRotation;

};

}