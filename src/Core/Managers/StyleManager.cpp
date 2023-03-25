#include "StyleManager.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include "../Systems/Logging.h"
#include "../Systems/Hash.h"
#include "GameGlobals.h"
#include <vector>

namespace CoreManagers
{


// -------------------------------------------------------
// -------------------------------------------------------
StyleManager g_StyleManager;


// -------------------------------------------------------
// -------------------------------------------------------
StyleManager::StyleManager()
{
    m_sStyleFilepath.append(__PROJECT_DIRECTORY__);
    m_sStyleFilepath.append("/src/Data/Styles.xml");
}


// -------------------------------------------------------
// -------------------------------------------------------
StyleManager::~StyleManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void StyleManager::InitializeStyleManager()
{
    rapidxml::file<> xmlFile(m_sStyleFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* textBlockNode = doc.first_node()->first_node("TextBlocks");
    for (rapidxml::xml_node<>* child = textBlockNode->first_node(); child; child = child->next_sibling())
    {
        TextBlockStyle textBlockStyle;
        textBlockStyle.m_uiID = CoreSystems::StringToHash32(std::string(child->first_attribute("ID")->value()));
        textBlockStyle.m_uiFont = CoreSystems::StringToHash32(std::string(child->first_attribute("Font")->value()));

        textBlockStyle.m_Color = ColorStringToSDLColor(child->first_attribute("Color")->value());

        textBlockStyle.m_sDefaultText = child->first_attribute("DefaultText")->value();

        m_TextBlockStyles.insert( { textBlockStyle.m_uiID, textBlockStyle } );
    }

    rapidxml::xml_node<>* buttonNode = doc.first_node()->first_node("Buttons");
    for (rapidxml::xml_node<>* child = buttonNode->first_node(); child; child = child->next_sibling())
    {
        ButtonStyle buttonStyle;
        buttonStyle.m_uiID = CoreSystems::StringToHash32(std::string(child->first_attribute("ID")->value()));
        buttonStyle.m_uiFont = CoreSystems::StringToHash32(std::string(child->first_attribute("Font")->value()));

        buttonStyle.m_HoverColor = ColorStringToSDLColor(child->first_attribute("HoverColor")->value());
        buttonStyle.m_PressedColor = ColorStringToSDLColor(child->first_attribute("PressedColor")->value());
        buttonStyle.m_TextColor = ColorStringToSDLColor(child->first_attribute("TextColor")->value());
        buttonStyle.m_BaseColor = ColorStringToSDLColor(child->first_attribute("BaseColor")->value());

        buttonStyle.m_sDefaultText = child->first_attribute("DefaultText")->value();

        m_ButtonStyles.insert( { buttonStyle.m_uiID, buttonStyle } );
    }

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Style Data Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
SDL_Color StyleManager::ColorStringToSDLColor(const char* string)
{
    std::vector<int> vTempVector;
    std::string sTempString = "";

    const uint8_t uiStringSize = static_cast<uint8_t>(std::strlen(string));
    for (uint8_t x=0; x < uiStringSize; ++x)
    {
        const char currChar = string[x];

        if (currChar == ' ')
        {
            vTempVector.push_back(std::stoi(sTempString));
            sTempString.clear();
        }
        else
        {
            sTempString += currChar;
        }
    }
    vTempVector.push_back(std::stoi(sTempString));

    SDL_Color output;
    if (vTempVector.size() == 4)
    {
        output.r = vTempVector[0];
        output.g = vTempVector[1];
        output.b = vTempVector[2];
        output.a = vTempVector[3];
    }
    else
    {
        CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eError, "Unable to load color from string!");
    }

    return output;
}

}