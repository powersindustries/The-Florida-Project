#include "AssetManager.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>

#include "Core/Systems/Systems.h"
#include "ItemManager.h"

#define DEFAULT_FONT_SIZE 24

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
AssetManager g_AssetManager;


// -------------------------------------------------------
// -------------------------------------------------------
AssetManager::AssetManager()
{
    m_sManifestFilepath.append(__PROJECT_DIRECTORY__);
    m_sManifestFilepath.append("/src/Data/AssetManifest.xml");

    m_sTextureDirectorypath.append(__PROJECT_DIRECTORY__);
    m_sTextureDirectorypath.append("/src/Assets/Textures/");

    m_sFontsDirectorypath.append(__PROJECT_DIRECTORY__);
    m_sFontsDirectorypath.append("/src/Assets/Fonts/");

    m_sSoundsDirectorypath.append(__PROJECT_DIRECTORY__);
    m_sSoundsDirectorypath.append("/src/Assets/Sounds/");

    m_sSaveDirectorypath.append(__PROJECT_DIRECTORY__);
    m_sSaveDirectorypath.append("/src/Data/Save.xml");
}


// -------------------------------------------------------
// -------------------------------------------------------
AssetManager::~AssetManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::InitialializeAssetManager(SDL_Renderer* renderer)
{
    LoadTextureAssets(renderer);
    LoadFontAssets(renderer);
    LoadSoundAssets();
    LoadMusicAssets();
}


// -------------------------------------------------------
// -------------------------------------------------------
SDL_Surface* AssetManager::GetAssetSurfaceByID(std::string AssetID)
{
    TextureAssetData& iconTextureData = m_TextureAssets[CoreSystems::StringToHash32(AssetID)];
    std::string sAssetPath = m_sTextureDirectorypath + iconTextureData.m_File;
    return IMG_Load(sAssetPath.c_str());
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::LoadTextureAssets(SDL_Renderer* renderer)
{
    rapidxml::file<> xmlFile(m_sManifestFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* texturesNode = doc.first_node()->first_node("Textures");
    for (rapidxml::xml_node<>* child = texturesNode->first_node(); child; child = child->next_sibling())
    {
        TextureAssetData textureAssetData;
        textureAssetData.m_ID = child->first_attribute("ID")->value();
        textureAssetData.m_File = child->first_attribute("File")->value();

        rapidxml::xml_attribute<>* framesAttribute = child->first_attribute("Frames");
        if (framesAttribute)
        {
            textureAssetData.m_uiFrames = std::stoi(framesAttribute->value());
        }
        else
        {
            textureAssetData.m_uiFrames = 0;
        }

        std::string sAssetPath = m_sTextureDirectorypath;
        sAssetPath.append(textureAssetData.m_File);

        SDL_Surface* surface = IMG_Load(sAssetPath.c_str());
        textureAssetData.m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        SDL_QueryTexture(textureAssetData.m_Texture, NULL, NULL, &textureAssetData.m_iWidth, &textureAssetData.m_iHeight);

        m_TextureAssets[CoreSystems::StringToHash32(textureAssetData.m_ID)] = textureAssetData;
    }

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Texture Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::LoadFontAssets(SDL_Renderer* renderer)
{
    rapidxml::file<> xmlFile(m_sManifestFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* fontNode = doc.first_node()->first_node("Fonts");
    for (rapidxml::xml_node<>* child = fontNode->first_node(); child; child = child->next_sibling())
    {
        FontAssetData fontAssetData;
        fontAssetData.m_ID = child->first_attribute("ID")->value();
        fontAssetData.m_File = child->first_attribute("File")->value();

        std::string assetPath = m_sFontsDirectorypath;
        assetPath.append(fontAssetData.m_File);
        fontAssetData.m_Font = TTF_OpenFont(assetPath.c_str(), DEFAULT_FONT_SIZE);

        m_FontAssets[CoreSystems::StringToHash32(fontAssetData.m_ID)] = fontAssetData;
    }

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Fonts Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::LoadSoundAssets()
{
    rapidxml::file<> xmlFile(m_sManifestFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* soundNode = doc.first_node()->first_node("Sounds");
    for (rapidxml::xml_node<>* child = soundNode->first_node(); child; child = child->next_sibling())
    {
        SoundAssetData soundAssetData;
        soundAssetData.m_ID = child->first_attribute("ID")->value();
        soundAssetData.m_File = child->first_attribute("File")->value();

        std::string assetPath = m_sSoundsDirectorypath;
        assetPath.append(soundAssetData.m_File);

        soundAssetData.m_SoundEffect = Mix_LoadWAV(assetPath.c_str());

        if (soundAssetData.m_SoundEffect)
        {
            m_SoundAssets[CoreSystems::StringToHash32(soundAssetData.m_ID)] = soundAssetData;
        }
        else
        {
            std::string errorMessage = "Sound asset unable to load: ";
            errorMessage.append(soundAssetData.m_ID);

            CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, errorMessage);
        }
    }

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Sounds Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::LoadMusicAssets()
{
    rapidxml::file<> xmlFile(m_sManifestFilepath.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    rapidxml::xml_node<>* musicNode = doc.first_node()->first_node("Music");
    for (rapidxml::xml_node<>* child = musicNode->first_node(); child; child = child->next_sibling())
    {
        MusicAssetData musicAssetData;
        musicAssetData.m_ID = child->first_attribute("ID")->value();
        musicAssetData.m_File = child->first_attribute("File")->value();

        std::string assetPath = m_sSoundsDirectorypath;
        assetPath.append(musicAssetData.m_File);

        musicAssetData.m_Music = Mix_LoadMUS(assetPath.c_str());

        if (musicAssetData.m_Music)
        {
            m_MusicAssets[CoreSystems::StringToHash32(musicAssetData.m_ID)] = musicAssetData;
        }
        else
        {
            std::string errorMessage = "Music asset unable to load: ";
            errorMessage.append(musicAssetData.m_ID);

            CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, errorMessage);
        }
    }

    CoreSystems::SYSTEMS_LOG(CoreSystems::LoggingLevel::eInfo, "Music Load Complete!");
}

}