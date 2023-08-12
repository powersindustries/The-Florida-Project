#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>


namespace Florida
{

struct GameStateData
{
    bool m_bApplicationRunning = false;
    bool m_bGamePaused = false;
    bool m_bGraphicsDebugMode = false;
    bool m_bDebugScreenActive = false;
    bool m_bGameOver = false;
    bool m_bIntroSeen = false;
};

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void Initialize(SDL_Renderer* renderer);
    void Update(float deltaTime);
    void Draw(SDL_Renderer* renderer);

    const bool ApplicationIsRunning() const { return m_GameStateData.m_bApplicationRunning; }
    const bool GameIsPaused() const         { return m_GameStateData.m_bGamePaused; }
    const bool GraphicsDebugModeOn() const  { return m_GameStateData.m_bGraphicsDebugMode; }
    const bool DebugScreenActive() const    { return m_GameStateData.m_bDebugScreenActive; }
    const bool IsGameOver() const           { return m_GameStateData.m_bGameOver; }
    const bool IntroSeen() const            { return m_GameStateData.m_bIntroSeen; }

    std::string GetEndGameOverMessageText() { return m_sEndGameMessage; };

    inline void SetIntroScreen(bool bHasBeenSeen) { m_GameStateData.m_bIntroSeen = bHasBeenSeen; };

    void SetGameRunning(bool bIsRunning);
    void SetGameIsPaused(bool bIsPaused);
    void SetGraphicsDebugModeOn(bool bGraphicsDebugOn);
    void SetDebugScreenActive(bool bDebugScreenActive);
    void SetGameOver(bool bGameOver);

    void StartNewGame();


private:

    void OnPreGameOverChanged();


private:

    GameStateData m_GameStateData;

    std::string m_sEndGameMessage;

};

extern GameManager g_GameManager;
}