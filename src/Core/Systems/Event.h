#pragma once
#include <vector>
#include <functional>

namespace Core
{

class Event
{
public:
    Event(){}
    ~Event(){}

    void SetEvent(std::function<void()>& inDelegate)
    {
        m_InFunction = inDelegate;
    }

    void OnBroadCast()
    {
        m_InFunction();
    }


private:

    std::function<void()> m_InFunction;

};

}
