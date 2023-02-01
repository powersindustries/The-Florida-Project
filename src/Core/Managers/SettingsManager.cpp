#include "SettingsManager.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <rapidxml_print.hpp>

#include "Core/Systems/Logging.h"
#include "GameGlobals.h"

namespace CoreManagers
{


// -------------------------------------------------------
// -------------------------------------------------------
SettingsManager g_SettingsManager;


// -------------------------------------------------------
// -------------------------------------------------------
SettingsManager::SettingsManager() 
    : m_MainWindow(nullptr)
{
    m_sSettingsFilepath.append(__PROJECT_DIRECTORY__);
    m_sSettingsFilepath.append("/src/Data/Settings.xml");

    m_SettingsData.m_iWidth = 0;
    m_SettingsData.m_iHeight = 0;

}


// -------------------------------------------------------
// -------------------------------------------------------
SettingsManager::~SettingsManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void SettingsManager::InitializeSettings()
{
    rapidxml::file<> xmlFile(m_sSettingsFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* settingsNode = doc.first_node("Settings");

    m_SettingsData.m_sTitle  = settingsNode->first_attribute("Title")->value();
    m_SettingsData.m_iWidth  = std::stoi(settingsNode->first_attribute("Width")->value());
    m_SettingsData.m_iHeight = std::stoi(settingsNode->first_attribute("Height")->value());
    
    m_SettingsData.m_iMusicVolumePercentage = std::stoi(settingsNode->first_attribute("MusicVolume")->value());
    m_SettingsData.m_iFXVolumePercentage    = std::stoi(settingsNode->first_attribute("FXVolume")->value());


    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Settings initialization complete.");
}


// -------------------------------------------------------
// -------------------------------------------------------
int SettingsManager::GetRelativeScreenX(int iX)
{
    const float fOutputX = (float)(iX * m_SettingsData.m_iWidth) / Florida::g_GameGlobals.BASE_WINDOW_SCALE_WIDTH;
    return static_cast<int>(fOutputX);
}


// -------------------------------------------------------
// -------------------------------------------------------
int SettingsManager::GetRelativeScreenY(int iY)
{
    const float fOutputY = (float)(iY * m_SettingsData.m_iHeight) / Florida::g_GameGlobals.BASE_WINDOW_SCALE_HEIGHT;
    return static_cast<int>(fOutputY);
}

}
