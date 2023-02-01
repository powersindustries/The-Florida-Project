#include "EventManager.h"
#include "Core/Systems/Assert.h"


namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
EventManager g_EventManager;


// -------------------------------------------------------
// -------------------------------------------------------
EventManager::EventManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
EventManager::~EventManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void EventManager::InitializeEvents()
{
    const uint16_t uiEventsCount = static_cast<uint16_t>(Events::eCount);
    m_EventsVector.reserve(uiEventsCount);

    for (uint16_t x = 0; x < uiEventsCount; ++x)
    {
        std::vector<CoreSystems::Event> newEvent;
        m_EventsVector.push_back(newEvent);

        m_EventsMap.insert({ static_cast<Events>(x), x });
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void EventManager::Broadcast(Events eEvent)
{
    CoreSystems::SYSTEMS_ASSERT(m_EventsMap.find(eEvent) != m_EventsMap.end());

    const uint16_t uiEventIndex = m_EventsMap[eEvent];
    std::vector<CoreSystems::Event> vEvents = m_EventsVector[uiEventIndex];

    const uint16_t uiEventsCount = static_cast<uint16_t>(vEvents.size());
    for (uint16_t x = 0; x < uiEventsCount; ++x)
    {
        vEvents[x].OnBroadCast();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void EventManager::Subscribe(Events eEvent, std::function<void()> inDelegate)
{
    CoreSystems::SYSTEMS_ASSERT(m_EventsMap.find(eEvent) != m_EventsMap.end());

    std::vector<CoreSystems::Event>& vEvents = m_EventsVector[m_EventsMap[eEvent]];

    CoreSystems::Event newSubscription;
    newSubscription.SetEvent(inDelegate);

    vEvents.push_back(newSubscription);
}

}