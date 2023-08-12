#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <string>


namespace Florida
{

enum class DayNightValues
{
    eDay,
    eNight
};

struct TimeData
{
    DayNightValues m_DayNight;
    uint16_t m_uiMinutes;

    uint16_t m_uiDayCount;
};

class GameplayManager
{
public:
    GameplayManager();
    ~GameplayManager();

    void InitializeGameManager();

    void Update(float deltaTime);

    const std::string GetDisplayTime();
    const std::string GetDisplayDayNight();

    inline const uint16_t GetDayCount() const { return m_TimeData.m_uiDayCount; };
    inline const DayNightValues GetDayNightValue() const { return m_TimeData.m_DayNight; };

    void SkipToNight();
    void GameOver();
    void ResetGameplayManager();


public:

    void DEBUG_IncreaseTimeOneHour();


private:

    TimeData m_TimeData;
    
    const float m_fMeleeTimer = 1.0f;
    float m_fMeleeTimeStamp = 0.0f;

};

extern GameplayManager g_GameplayManager;
}