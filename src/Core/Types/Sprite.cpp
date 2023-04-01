#include "Sprite.h"
#include "Game/Managers/AssetManager.h"

namespace Core
{


// -------------------------------------------------------
// -------------------------------------------------------
Sprite::Sprite()
    : m_Texture(nullptr)
{
    m_SpriteType = SpriteType::eNonAnimated;

    m_uiFrameNumber    = 0;
    m_uiAnimationSpeed = 0;

    m_dRotation = 0.0;

    m_SourceRectangle.x = 0;
    m_SourceRectangle.y = 0;
    m_SourceRectangle.w = 0;
    m_SourceRectangle.h = 0;

    m_DestinationRectangle.x = 0;
    m_DestinationRectangle.y = 0;
    m_DestinationRectangle.w = 0;
    m_DestinationRectangle.h = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
Sprite::~Sprite()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
Sprite::Sprite(uint32_t assetIDHash, SpriteType spriteType)
    : m_Texture(nullptr)
{
    m_SpriteType = spriteType;

    m_uiFrameNumber    = 0;
    m_uiAnimationSpeed = 0;

    m_dRotation = 0.0;

    SetTexture(assetIDHash);

    m_SourceRectangle.x = 0;
    m_SourceRectangle.y = 0;
    m_SourceRectangle.w = 0;
    m_SourceRectangle.h = 0;

    m_DestinationRectangle.x = 0;
    m_DestinationRectangle.y = 0;
    m_DestinationRectangle.w = 0;
    m_DestinationRectangle.h = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
Sprite::Sprite(uint32_t assetIDHash, uint8_t animationSpeed, SpriteType spriteType)
{
    SetTexture(assetIDHash);

    m_SpriteType = spriteType;
    m_uiAnimationSpeed = animationSpeed;

    m_dRotation = 0.0;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::Update(float deltaTime)
{
    // Update Source Rectangle to next frame in spritesheet.
    // Spritesheets work horizontally for now. Will eventually be vertical instead.
    if (m_SpriteType == SpriteType::eAnimanted)
    {
        m_SourceRectangle.y = m_SourceRectangle.h * static_cast<int>(SDL_GetTicks() / m_uiAnimationSpeed % m_uiFrameNumber);
    }

    // Update Destination Rectangle
    m_DestinationRectangle.x = m_Transform.m_iPositionX;
    m_DestinationRectangle.y = m_Transform.m_iPositionY;
    m_DestinationRectangle.w = m_Transform.m_iWidth * m_Transform.m_iScale;
    m_DestinationRectangle.h = m_Transform.m_iHeight * m_Transform.m_iScale;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::Update(float deltaTime, SDL_Rect& inRectangle)
{
    // Update Transform Data.
    m_Transform.SetTransform(inRectangle);

    // Update Source Rectangle if animated.
    if (m_SpriteType == SpriteType::eAnimanted)
    {
        m_SourceRectangle.y = m_SourceRectangle.h * static_cast<int>(SDL_GetTicks() / m_uiAnimationSpeed % m_uiFrameNumber);
    }

    // Update Destination Rectangle.
    m_DestinationRectangle.x = m_Transform.m_iPositionX;
    m_DestinationRectangle.y = m_Transform.m_iPositionY;
    m_DestinationRectangle.w = m_Transform.m_iWidth * m_Transform.m_iScale;
    m_DestinationRectangle.h = m_Transform.m_iHeight * m_Transform.m_iScale;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip)
{
    if (m_SpriteType == SpriteType::eAnimanted)
    {
        SDL_RenderCopyEx(renderer, m_Texture, &m_SourceRectangle, &m_DestinationRectangle, m_dRotation, NULL, flip);
    }
    else
    {
        SDL_RenderCopyEx(renderer, m_Texture, NULL, &m_DestinationRectangle, m_dRotation, NULL, flip);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::SetTexture(uint32_t textureIDHash)
{
    Florida::TextureAssetData& textureAssetData =  Florida::g_AssetManager.m_TextureAssets[textureIDHash];
    m_Texture = textureAssetData.m_Texture;
    m_uiFrameNumber = textureAssetData.m_uiFrames;
    
    m_SourceRectangle.x = 0;
    m_SourceRectangle.y = 0;
    m_SourceRectangle.w = textureAssetData.m_iWidth;
    m_SourceRectangle.h = m_uiFrameNumber == 0 ? textureAssetData.m_iHeight : textureAssetData.m_iHeight / m_uiFrameNumber;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::SetRotation(double degrees)
{
    m_dRotation = degrees;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Sprite::SetPosition(SDL_Rect inRectangle)
{
    m_Transform.SetTransform(inRectangle);

    m_DestinationRectangle.x = m_Transform.m_iPositionX;
    m_DestinationRectangle.y = m_Transform.m_iPositionY;
    m_DestinationRectangle.w = m_Transform.m_iWidth * m_Transform.m_iScale;
    m_DestinationRectangle.h = m_Transform.m_iHeight * m_Transform.m_iScale;
}

}
