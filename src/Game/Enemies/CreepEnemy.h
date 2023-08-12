#pragma once
#include <SDL.h> // SDL Main
#include <SDL_image.h> // SDL Image
#include <vector>

#include "EnemyBase.h"

using namespace Core;

namespace Florida
{

enum class CreepState
{
    eMoving,        // Slowly move towards the player's position.
    ePreAttack,     // Right before reaching the player, stop and get ready to attack.
    eAttack,        // Apply damage to player.
    ePostAttack     // Stop for a moment and get ready to move again.
};

class CreepEnemy : public EnemyBase
{
public:
    CreepEnemy();
    ~CreepEnemy();

    void Update(float deltaTime) override;
    void Draw(SDL_Renderer* renderer) override;

    void SetPosition(int x, int y) override;

    void KillEnemy() override;


private:

    CreepState m_State;

    const uint8_t m_uiMinSpeed = 1;
    const uint8_t m_uiMaxSpeed = 3;
    uint8_t m_uiSpeed = 2;

    const uint8_t m_uiItemDropRate = 33;
    std::vector<uint32_t> m_DroppableItems;

    const uint8_t m_uiDamageAmount = 1;
    const double m_iAttackRange = 20.0;
    const double m_iDamageRange = 23.0;

    const float m_fUpdateTimer = 0.05f; // 3 frames.
    float m_fUpdateTimeStamp   = 0.0f;

    const float m_fPreAttackTimer = 0.4f; // 24 seconds.
    float m_fPreAttackTimeStamp   = 0.0f;

    const float m_fPostAttackTimer = 0.35f; // 21 seconds.
    float m_fPostAttackTimeStamp   = 0.0f;

};
}