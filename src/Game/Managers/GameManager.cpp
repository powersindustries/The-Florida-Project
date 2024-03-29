#include "GameManager.h"
#include "UIManager.h"
#include "MapManager.h"
#include "AssetManager.h"
#include "EnemyManager.h"
#include "EventManager.h"
#include "GameplayManager.h"
#include "CraftingManager.h"
#include "ItemManager.h"
#include "SoundManager.h"
#include "Core/Systems/Hash.h"
#include "../Player/Player.h"

#define MAP_ID "mp_Main"
#define BACKGROUND_MUSIC_ID "ms_Ambiance"

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
GameManager g_GameManager;


// -------------------------------------------------------
// -------------------------------------------------------
GameManager::GameManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
GameManager::~GameManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameManager::Initialize(SDL_Renderer* renderer)
{
    g_AssetManager.Initialize(renderer);

    g_ItemManager.Initialize();
    g_MapManager.InitialLoad();
    g_CraftingManager.Initialize();
    g_Player.Initialize();
    g_UIManager.Initialize();
    g_EnemyManager.Initialize();

    m_GameStateData.m_bApplicationRunning = true;

    StartNewGame();

    m_GameStateData.m_bGamePaused = true;

    g_EventManager.Subscribe(Events::ePreGameOverChanged, [this]() { GameManager::OnPreGameOverChanged(); });
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameManager::Update(float deltaTime)
{
    if (m_GameStateData.m_bGameOver)
    {
        g_UIManager.Update(deltaTime);
        return;
    }

    if (Core::g_InputManager.GetActionPressed(Core::InputMappings::eESCMenu) && IntroSeen())
    {
        if (g_UIManager.GetActiveScreenID() == UIScreenID::ePause)
        {
            g_UIManager.RemoveScreen(UIScreenID::ePause);
        }
        else
        {
            g_UIManager.ActivateScreen(UIScreenID::ePause);
        }
    }

    if (!m_GameStateData.m_bGameOver && Core::g_InputManager.GetActionPressed(Core::InputMappings::eTabMenu) && IntroSeen())
    {
        if (g_UIManager.GetActiveScreenID() == UIScreenID::eInventory)
        {
            g_UIManager.RemoveScreen(UIScreenID::eInventory);
        }
        else
        {
            g_UIManager.ActivateScreen(UIScreenID::eInventory);
        }
    }

    if (!m_GameStateData.m_bGameOver && Core::g_InputManager.GetActionPressed(Core::InputMappings::eDebug1))
    {
        m_GameStateData.m_bGraphicsDebugMode = !m_GameStateData.m_bGraphicsDebugMode;
    }

    if (!m_GameStateData.m_bGameOver && Core::g_InputManager.GetActionPressed(Core::InputMappings::eDebug4))
    {
        m_GameStateData.m_bDebugScreenActive = !m_GameStateData.m_bDebugScreenActive;
    }

    g_UIManager.Update(deltaTime);

    if (!m_GameStateData.m_bGamePaused)
    {
        g_GameplayManager.Update(deltaTime);

        g_Player.Update(deltaTime);
        g_MapManager.Update(deltaTime);
        g_EnemyManager.Update(deltaTime);
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameManager::Draw(SDL_Renderer* renderer)
{
    g_MapManager.Draw(renderer);
    g_EnemyManager.Draw(renderer);
    g_Player.Draw(renderer);

    g_UIManager.Draw(renderer);
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameManager::SetGameRunning(bool bIsRunning)
{
    m_GameStateData.m_bApplicationRunning = bIsRunning;
    g_EventManager.Broadcast(Events::eGameRunningChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameManager::SetGameIsPaused(bool bIsPaused)
{
    m_GameStateData.m_bGamePaused = bIsPaused;
    g_EventManager.Broadcast(Events::eGamePausedChaned);
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameManager::SetGraphicsDebugModeOn(bool bGraphicsDebugOn)
{
    m_GameStateData.m_bGraphicsDebugMode = bGraphicsDebugOn;
    g_EventManager.Broadcast(Events::eGraphicsDebugChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameManager::SetDebugScreenActive(bool bDebugScreenActive)
{
    m_GameStateData.m_bDebugScreenActive = bDebugScreenActive;
    g_EventManager.Broadcast(Events::eDebugScreenChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameManager::SetGameOver(bool bGameOver)
{
    m_GameStateData.m_bGameOver = bGameOver;
    g_EventManager.Broadcast(Events::ePreGameOverChanged);
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameManager::StartNewGame()
{
    g_GameplayManager.ResetGameplayManager();
    g_ItemManager.ResetItemManager();
    g_MapManager.ResetMapManager();
    g_Player.ResetPlayer();
    g_EnemyManager.ResetEnemyManager();
    g_SoundManager.ResetSoundManager();

    uint32_t mapIDHash = Core::StringToHash32(std::string(MAP_ID));
    g_MapManager.LoadMapByID(mapIDHash);

    g_UIManager.ResetUIManager();

    m_GameStateData.m_bApplicationRunning = true;
    m_GameStateData.m_bGamePaused         = false;
    m_GameStateData.m_bGraphicsDebugMode  = false;
    m_GameStateData.m_bDebugScreenActive  = false;
    m_GameStateData.m_bGameOver           = false;

    if (IntroSeen())
    {
        g_SoundManager.PlayMusicByID(BACKGROUND_MUSIC_ID);
    }

}


// -------------------------------------------------------
// -------------------------------------------------------
void GameManager::OnPreGameOverChanged()
{
    if (m_GameStateData.m_bGameOver)
    {
        m_sEndGameMessage = "You survived ";
        m_sEndGameMessage.append( std::to_string(g_GameplayManager.GetDayCount() + 1) );
        m_sEndGameMessage.append(" day and killed ");
        m_sEndGameMessage.append( std::to_string(g_EnemyManager.GetEnemiesKilledCount()) );
        m_sEndGameMessage.append(" enemies.");
    }

    g_EventManager.Broadcast(Events::eGameOverChanged);
}

}