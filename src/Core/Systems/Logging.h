#pragma once
#include <Windows.h>
#include <string>

namespace CoreSystems
{


enum class LoggingLevel
{
    eInfo,
    eWarning,
    eError
};


// -------------------------------------------------------
// -------------------------------------------------------
static void SYSTEMS_LOG(const LoggingLevel level, const std::string& message)
{
    std::string sOutputMessage;
    switch (level)
    {
    case LoggingLevel::eInfo:
    {
        sOutputMessage.append("INFO: ");
        break;
    }
    case LoggingLevel::eWarning:
    {
        sOutputMessage.append("WARNING: ");
        break;
    }
    case LoggingLevel::eError:
    {
        sOutputMessage.append("ERROR: ");
        break;
    }
    default:
    {
        // Default to info if LoggingLevel doesnt exist.
        sOutputMessage.append("INFO: ");
        break;
    }
    }

    sOutputMessage.append(message);
    sOutputMessage.push_back('\n');

    OutputDebugString(sOutputMessage.c_str());
}


// -------------------------------------------------------
// -------------------------------------------------------
static void SYSTEMS_LOG(const LoggingLevel level, const char* message)
{
    std::string sOutputMessage;
    switch (level)
    {
    case LoggingLevel::eInfo:
    {
        sOutputMessage.append("INFO: ");
        break;
    }
    case LoggingLevel::eWarning:
    {
        sOutputMessage.append("WARNING: ");
        break;
    }
    case LoggingLevel::eError:
    {
        sOutputMessage.append("ERROR: ");
        break;
    }
    default:
    {
        // Default to info if LoggingLevel doesnt exist.
        sOutputMessage.append("INFO: ");
        break;
    }
    }

    sOutputMessage.append(message);
    sOutputMessage.push_back('\n');

    OutputDebugString(sOutputMessage.c_str());
}

}