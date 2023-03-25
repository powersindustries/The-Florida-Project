#include "Game.h"
#include "GameGlobals.h"
#include "Game/Player/Player.h"
#include "Systems/Logging.h"
#include "Game/Managers/AssetManager.h"
#include "Game/Managers/UIManager.h"
#include "Game/Managers/MapManager.h"
#include "Game/Managers/EventManager.h"
#include "Game/Managers/EnemyManager.h"
#include "Managers/SettingsManager.h"
#include "Managers/InputManager.h"
#include "Game/Managers/GameManager.h"
#include "Managers/StyleManager.h"

#define MIX_FREQUENCY 44100
#define MIX_CHUNK_SIZE 2048
#define MIX_CHANNEL_COUND 2


namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
SDL_Renderer* Game::m_Renderer;
GameGlobals g_GameGlobals;


// -------------------------------------------------------
// -------------------------------------------------------
Game::Game()
    : m_Window(nullptr)
{
    m_fDeltaTime = 0.0f;
    m_uiTicksLastFrame = 0;

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Game was created.");
}


// -------------------------------------------------------
// -------------------------------------------------------
Game::~Game()
{
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Game was destroyed.");
}


// -------------------------------------------------------
// -------------------------------------------------------
void Game::InitializeSession()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Error with SDL_Init.");
        return;
    }

    if (TTF_Init() != 0)
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Error with TTF_Init.");
        return;
    }

    if (Mix_OpenAudio(MIX_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_CHANNEL_COUND, MIX_CHUNK_SIZE) < 0)
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Error with MixerOpenAudio.");
        return;
    }

    // Initialize Core.
    CoreManagers::g_SettingsManager.InitializeSettings();
    g_EventManager.InitializeEvents();
    CoreManagers::g_StyleManager.InitializeStyleManager();

    // Create Window.
    m_Window = SDL_CreateWindow(
        CoreManagers::g_SettingsManager.GetTitle().c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        CoreManagers::g_SettingsManager.GetScreenWidth(),
        CoreManagers::g_SettingsManager.GetScreenHeight(),
        SDL_WINDOW_SHOWN);

    if (!m_Window)
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Window did not work.");
        return;
    }

    // -1 is default driver.
    m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);

    if (!m_Renderer)
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Renderer did not work.");
        return;
    }

    g_GameManager.InitializeGameManager(m_Renderer);


    // Set Window Icon.
    SDL_SetWindowIcon(m_Window, g_AssetManager.GetAssetSurfaceByID("txt_WindowsIcon"));

    return;
}


// -------------------------------------------------------
// -------------------------------------------------------
void Game::EndSession()
{
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    SDL_Quit();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Game::ProcessInputs()
{
    CoreManagers::g_InputManager.ProcessInputs();
}


// -------------------------------------------------------
// -------------------------------------------------------
void Game::Update()
{
    // Wait 16ms since last frame to reach 60fps
    int timeToWait = g_GameGlobals.FRAME_TARGET_TIME - (SDL_GetTicks() - m_uiTicksLastFrame);

    if (timeToWait > 0 && timeToWait <= g_GameGlobals.FRAME_TARGET_TIME)
    {
        SDL_Delay(timeToWait);
    }


    // Update Loop here
    uint32_t sdlTicks = SDL_GetTicks();
    m_fDeltaTime = sdlTicks / 1000.0f;
    m_uiTicksLastFrame = sdlTicks;

    g_GameManager.Update(m_fDeltaTime);

}


// -------------------------------------------------------
// -------------------------------------------------------
void Game::Draw()
{
    SDL_SetRenderDrawColor(m_Renderer,
        g_GameGlobals.COLOR_WHITE.r,
        g_GameGlobals.COLOR_WHITE.g,
        g_GameGlobals.COLOR_WHITE.b,
        g_GameGlobals.COLOR_WHITE.a);
    SDL_RenderClear(m_Renderer);

    SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);

    g_GameManager.Draw(m_Renderer);

    SDL_RenderPresent(m_Renderer);
}

}