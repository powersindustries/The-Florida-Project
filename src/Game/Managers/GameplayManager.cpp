#include "GameplayManager.h"
#include "EventManager.h"
#include "GameManager.h"

#define TIME_INCREASE 4
#define MINUTES_PER_HOUR 60
#define MINUTES_PER_12_HOURS 720
#define DEFAULT_STARTING_MINUTES 500

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
GameplayManager g_GameplayManager;


// -------------------------------------------------------
// -------------------------------------------------------
GameplayManager::GameplayManager()
{
    ResetGameplayManager();
}


// -------------------------------------------------------
// -------------------------------------------------------
GameplayManager::~GameplayManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameplayManager::InitializeGameManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameplayManager::Update(float* deltaTime)
{
    if (*deltaTime > (m_fMeleeTimeStamp + m_fMeleeTimer))
    {
        m_fMeleeTimeStamp = *deltaTime;

        m_TimeData.m_uiMinutes += TIME_INCREASE;

        // Day or Night has ended. Reset the clock.
        if (m_TimeData.m_uiMinutes >= MINUTES_PER_12_HOURS)
        {
            // Increment to next day.
            if (m_TimeData.m_DayNight == DayNightValues::eNight)
            {
                m_TimeData.m_uiDayCount++;

                g_EventManager.Broadcast(Events::eDayCountChanged);
            }

            m_TimeData.m_DayNight = m_TimeData.m_DayNight == DayNightValues::eDay ? DayNightValues::eNight : DayNightValues::eDay;

            m_TimeData.m_uiMinutes = 0;

            g_EventManager.Broadcast(Events::eDayNightChanged);
        }
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
const std::string GameplayManager::GetDisplayTime()
{
    std::string output;

    double hoursFromMinutes = static_cast<double>(m_TimeData.m_uiMinutes) / MINUTES_PER_HOUR;
    double intPart;
    double fractPart = modf(hoursFromMinutes, &intPart);

    int hoursAmount = static_cast<int>(hoursFromMinutes);
    std::string hoursText;
    if (hoursAmount == 0)
    {
        hoursText = "12";
    }
    else
    {
        hoursText = hoursAmount >= 10 ? std::to_string(hoursAmount) : ("0" + std::to_string(hoursAmount));
    }

    int minutesAmount = static_cast<int>(fractPart * MINUTES_PER_HOUR);
    std::string minutesText = minutesAmount >= 10 ? std::to_string(minutesAmount) : ("0" + std::to_string(minutesAmount));

    output.append(hoursText);
    output.append(":");
    output.append(minutesText);

    return output;
}


// -------------------------------------------------------
// -------------------------------------------------------
const std::string GameplayManager::GetDisplayDayNight()
{
    if (m_TimeData.m_DayNight == DayNightValues::eDay)
    {
        return std::string("Day");
    }
    else
    {
        return std::string("Night");
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameplayManager::SkipToNight()
{
    m_TimeData.m_DayNight = DayNightValues::eNight;
    m_TimeData.m_uiMinutes = 0;

    g_EventManager.Broadcast(Events::eDayNightChanged);
}



// -------------------------------------------------------
// -------------------------------------------------------
void GameplayManager::GameOver()
{
    g_GameManager.SetGameOver(true);
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameplayManager::ResetGameplayManager()
{
    m_TimeData.m_DayNight = DayNightValues::eDay;
    m_TimeData.m_uiMinutes = DEFAULT_STARTING_MINUTES;
    m_TimeData.m_uiDayCount = 0;
}


// -------------------------------------------------------
// -------------------------------------------------------
void GameplayManager::DEBUG_IncreaseTimeOneHour()
{
    m_TimeData.m_uiMinutes += 30; 
}

}