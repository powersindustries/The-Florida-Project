#include "AssetManager.h"

#include "Core/Systems/Systems.h"
#include "Core/Types/LuaTableLoader.h"
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
    m_sManifestFilepath.append("/src/Data/AssetManifest.lua");

    m_sTextureDirectorypath.append(__PROJECT_DIRECTORY__);
    m_sTextureDirectorypath.append("/src/Assets/Textures/");

    m_sFontsDirectorypath.append(__PROJECT_DIRECTORY__);
    m_sFontsDirectorypath.append("/src/Assets/Fonts/");

    m_sSoundsDirectorypath.append(__PROJECT_DIRECTORY__);
    m_sSoundsDirectorypath.append("/src/Assets/Sounds/");
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
    TextureAssetData& iconTextureData = m_TextureAssets[Core::StringToHash32(AssetID)];
    std::string sAssetPath = m_sTextureDirectorypath + iconTextureData.m_File;
    return IMG_Load(sAssetPath.c_str());
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::LoadTextureAssets(SDL_Renderer* renderer)
{
	Core::LuaTableLoader* luaLoader = new Core::LuaTableLoader(m_sManifestFilepath);

	// Load Textures table.
	luaLoader->LoadTableByID("Textures");

	const uint8_t uiTexturesTableSize = luaLoader->GetCurrentTableSize();
	for (uint8_t x = 0; x < uiTexturesTableSize; ++x)
	{
		int indexOffset = x + 1;

		if (luaLoader->PushIntegerAndGetTable(indexOffset))
		{
			break;
		}

		TextureAssetData textureAssetData;
		textureAssetData.m_ID = luaLoader->GetStringByID("ID");
		textureAssetData.m_File = luaLoader->GetStringByID("File");
		textureAssetData.m_uiFrames = luaLoader->GetIntByID("Frames");

		std::string sAssetPath = m_sTextureDirectorypath;
		sAssetPath.append(textureAssetData.m_File);

		SDL_Surface* surface = IMG_Load(sAssetPath.c_str());
		textureAssetData.m_Texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		SDL_QueryTexture(textureAssetData.m_Texture, NULL, NULL, &textureAssetData.m_iWidth, &textureAssetData.m_iHeight);

		m_TextureAssets[Core::StringToHash32(textureAssetData.m_ID)] = textureAssetData;

		luaLoader->PopTopTableElement();
	}

	delete luaLoader;


	Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Texture Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::LoadFontAssets(SDL_Renderer* renderer)
{
	Core::LuaTableLoader* luaLoader = new Core::LuaTableLoader(m_sManifestFilepath);

	// Load Textures table.
	luaLoader->LoadTableByID("Fonts");

	const uint8_t uiFontsTableSize = luaLoader->GetCurrentTableSize();
	for (uint8_t x = 0; x < uiFontsTableSize; ++x)
	{
		int indexOffset = x + 1;

		if (luaLoader->PushIntegerAndGetTable(indexOffset))
		{
			break;
		}

		FontAssetData fontAssetData;
		fontAssetData.m_ID = luaLoader->GetStringByID("ID");
		fontAssetData.m_File = luaLoader->GetStringByID("File");

		std::string assetPath = m_sFontsDirectorypath;
		assetPath.append(fontAssetData.m_File);
		fontAssetData.m_Font = TTF_OpenFont(assetPath.c_str(), DEFAULT_FONT_SIZE);

		m_FontAssets[Core::StringToHash32(fontAssetData.m_ID)] = fontAssetData;

		luaLoader->PopTopTableElement();
	}

	delete luaLoader;


	Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Fonts Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::LoadSoundAssets()
{
	Core::LuaTableLoader* luaLoader = new Core::LuaTableLoader(m_sManifestFilepath);

	// Load Textures table.
	luaLoader->LoadTableByID("Sounds");

	const uint8_t uiSoundsTableSize = luaLoader->GetCurrentTableSize();
	for (uint8_t x = 0; x < uiSoundsTableSize; ++x)
	{
		int indexOffset = x + 1;

		if (luaLoader->PushIntegerAndGetTable(indexOffset))
		{
			break;
		}

		SoundAssetData soundAssetData;
		soundAssetData.m_ID = luaLoader->GetStringByID("ID");
		soundAssetData.m_File = luaLoader->GetStringByID("File");

		std::string assetPath = m_sSoundsDirectorypath;
		assetPath.append(soundAssetData.m_File);

		soundAssetData.m_SoundEffect = Mix_LoadWAV(assetPath.c_str());

		if (soundAssetData.m_SoundEffect)
		{
			m_SoundAssets[Core::StringToHash32(soundAssetData.m_ID)] = soundAssetData;
		}
		else
		{
			std::string errorMessage = "Sound asset unable to load: ";
			errorMessage.append(soundAssetData.m_ID);

			Core::SYSTEMS_LOG(Core::LoggingLevel::eError, errorMessage.c_str());
		}

		luaLoader->PopTopTableElement();
	}

	delete luaLoader;


	Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Sounds Load Complete!");
}


// -------------------------------------------------------
// -------------------------------------------------------
void AssetManager::LoadMusicAssets()
{
	Core::LuaTableLoader* luaLoader = new Core::LuaTableLoader(m_sManifestFilepath);

	// Load Textures table.
	luaLoader->LoadTableByID("Music");

	const uint8_t uiMusicTableSize = luaLoader->GetCurrentTableSize();
	for (uint8_t x = 0; x < uiMusicTableSize; ++x)
	{
		int indexOffset = x + 1;

		if (luaLoader->PushIntegerAndGetTable(indexOffset))
		{
			break;
		}

		MusicAssetData musicAssetData;
		musicAssetData.m_ID = luaLoader->GetStringByID("ID");
		musicAssetData.m_File = luaLoader->GetStringByID("File");

		std::string assetPath = m_sSoundsDirectorypath;
		assetPath.append(musicAssetData.m_File);

		musicAssetData.m_Music = Mix_LoadMUS(assetPath.c_str());

		if (musicAssetData.m_Music)
		{
			m_MusicAssets[Core::StringToHash32(musicAssetData.m_ID)] = musicAssetData;
		}
		else
		{
			std::string errorMessage = "Music asset unable to load: ";
			errorMessage.append(musicAssetData.m_ID);

			Core::SYSTEMS_LOG(Core::LoggingLevel::eError, errorMessage.c_str());
		}

		luaLoader->PopTopTableElement();
	}

	delete luaLoader;


	Core::SYSTEMS_LOG(Core::LoggingLevel::eInfo, "Music Load Complete!");
}

}