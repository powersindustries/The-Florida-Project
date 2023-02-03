#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <vector>
#include <unordered_map>

#include "../Enemies/EnemyBase.h"

namespace Florida
{


struct EnemySpawnerData
{
    uint32_t m_uiMapIDHash;
    SDL_Rect m_Rectangle;
};


class EnemyManager
{
public:
    EnemyManager();
    ~EnemyManager();

    void InitializeEnemyManager();
    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);

    void SetupEnemySpawning(std::vector<uint32_t>& SpawnersVector);

    void ResetEnemyManager();

    inline const uint16_t GetEnemiesKilledCount() { return m_uiEnemiesKilled; }


private:

    void SpawnNewEnemy();

    void OnDayNightChangedEvent();

    void OnEnemyDiedEvent();


public:

    std::vector<EnemyBase*> m_ActiveEnemies;

    std::vector<uint32_t> m_ActiveEnemySpawners;

    std::vector<EnemySpawnerData> m_EnemySpawnerVector;
    std::unordered_map<uint32_t, uint32_t> m_EnemySpawnerMap; // Key: m, Value: index in m_EnemiesVector


private:

    uint16_t m_uiEnemiesKilled;

    const float m_fSpawnTimer = 2.5f;
    float m_fSpawnerTimeStamp = 0.0f;

};

extern EnemyManager g_EnemyManager;

}