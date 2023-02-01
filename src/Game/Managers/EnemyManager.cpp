#include "EnemyManager.h"
#include <time.h>
#include <algorithm>

#include "MapManager.h"
#include "EventManager.h"
#include "GameplayManager.h"
#include "GameManager.h"
#include "../Enemies/CreepEnemy.h"
#include "Core/Systems/Logging.h"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
EnemyManager g_EnemyManager;


// -------------------------------------------------------
// -------------------------------------------------------
EnemyManager::EnemyManager()
{
    srand(static_cast<unsigned int>(time(NULL)));

    m_uiEnemiesKilled = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
EnemyManager::~EnemyManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void EnemyManager::InitializeEnemyManager()
{
    g_EventManager.Subscribe(Events::eDayNightChanged, [this]() { EnemyManager::OnDayNightChangedEvent(); });
    g_EventManager.Subscribe(Events::eEnemyDied, [this]() { EnemyManager::OnEnemyDiedEvent(); });
}


// -------------------------------------------------------
// -------------------------------------------------------
void EnemyManager::Update(float* deltaTime)
{
    if (g_GameplayManager.GetDayNightValue() == DayNightValues::eDay)
    {
        return;
    }


    if (*deltaTime > (m_fSpawnerTimeStamp + m_fSpawnTimer))
    {
        m_fSpawnerTimeStamp = *deltaTime;

        SpawnNewEnemy();
    }

    const uint32_t uiEnemyCount = static_cast<uint32_t>(m_ActiveEnemies.size());
    for (uint32_t x = 0; x < uiEnemyCount; ++x)
    {
        EnemyBase* currEnemy = m_ActiveEnemies[x];
        if (currEnemy->m_bActive)
        {
            currEnemy->Update(deltaTime);
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void EnemyManager::Draw(SDL_Renderer* renderer)
{
    if (g_GameplayManager.GetDayNightValue() == DayNightValues::eDay)
    {
        return;
    }

    if (g_GameManager.GraphicsDebugModeOn())
    {
        const uint32_t uiSpawnerCount = static_cast<uint32_t>(m_ActiveEnemySpawners.size());
        for (uint32_t x = 0; x < uiSpawnerCount; ++x)
        {
            EnemySpawnerData& currSpawnerData = m_EnemySpawnerVector[m_ActiveEnemySpawners[x]];

            SDL_SetRenderDrawColor(renderer, g_GameGlobals.COLOR_RED.r, g_GameGlobals.COLOR_RED.g, g_GameGlobals.COLOR_RED.b, g_GameGlobals.COLOR_RED.a);
            SDL_RenderFillRect(renderer, &currSpawnerData.m_Rectangle);
        }
    }

    const uint32_t uiEnemyCount = static_cast<uint32_t>(m_ActiveEnemies.size());
    for (uint32_t x = 0; x < uiEnemyCount; ++x)
    {
        EnemyBase* currEnemyData = m_ActiveEnemies[x];
        if (currEnemyData->m_bActive)
        {
            currEnemyData->Draw(renderer);
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void EnemyManager::SetupEnemySpawning(std::vector<uint32_t>& SpawnersVector)
{
    m_ActiveEnemySpawners.clear();
    m_ActiveEnemySpawners = g_MapManager.m_ActiveMap->m_EnemySpawners;
}


// -------------------------------------------------------
// -------------------------------------------------------
void EnemyManager::ResetEnemyManager()
{
    m_ActiveEnemies.clear();

    m_uiEnemiesKilled = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
void EnemyManager::SpawnNewEnemy()
{
    const uint32_t uiSpawnerCount = static_cast<uint32_t>(m_ActiveEnemySpawners.size());
    if (uiSpawnerCount > 0)
    {
        const uint32_t uiActiveSpawnerIndex = m_ActiveEnemySpawners[0];
        EnemySpawnerData& randSpawner = m_EnemySpawnerVector[uiActiveSpawnerIndex];

        EnemyBase* newCreep = new CreepEnemy;
        newCreep->SetPosition(randSpawner.m_Rectangle.x, randSpawner.m_Rectangle.y + randSpawner.m_Rectangle.h - newCreep->m_BaseRectangle.h);
        m_ActiveEnemies.push_back(newCreep);

        std::random_shuffle(m_ActiveEnemySpawners.begin(), m_ActiveEnemySpawners.end());
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void EnemyManager::OnDayNightChangedEvent()
{
    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Enemies deleted.");

    m_ActiveEnemies.clear();
}


// -------------------------------------------------------
// -------------------------------------------------------
void EnemyManager::OnEnemyDiedEvent()
{
   m_uiEnemiesKilled++;
}

}