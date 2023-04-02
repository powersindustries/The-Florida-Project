#pragma once
#include <SDL.h> // SDL Main
#include <SDL_ttf.h> // SDL Fonts or Text
#include <SDL_image.h> // SDL Image
#include <SDL_mixer.h>
#include <map>
#include <string>



namespace Florida
{


struct TextureAssetData
{
    TextureAssetData() : m_Texture(nullptr), m_iHeight(0), m_iWidth(0), m_uiFrames(0) {}

    std::string m_ID;
    std::string m_File;

    SDL_Texture* m_Texture;

    uint8_t m_uiFrames;

    int m_iWidth;
    int m_iHeight;
};


struct FontAssetData
{
    FontAssetData() : m_Font(nullptr) {}

    std::string m_ID;
    std::string m_File;

    TTF_Font* m_Font;
};


struct SoundAssetData
{
    SoundAssetData() : m_SoundEffect(nullptr) {}

    std::string m_ID;
    std::string m_File;

    Mix_Chunk* m_SoundEffect;
};


struct MusicAssetData
{
    MusicAssetData() : m_Music(nullptr) {}

    std::string m_ID;
    std::string m_File;

    Mix_Music* m_Music;
};


class AssetManager
{
public:
    AssetManager();
    ~AssetManager();

    void InitialializeAssetManager(SDL_Renderer* renderer);

    SDL_Surface* GetAssetSurfaceByID(std::string AssetID);

    std::map<uint32_t, TextureAssetData> m_TextureAssets; // ID as hash, Texture Data
    std::map<uint32_t, FontAssetData> m_FontAssets; // ID as hash, Font Data
    std::map<uint32_t, SoundAssetData> m_SoundAssets; // ID as hash, Sound Data
    std::map<uint32_t, MusicAssetData> m_MusicAssets; // ID as hash, Music Data


private:

    void LoadTextureAssets(SDL_Renderer* renderer);
    void LoadFontAssets(SDL_Renderer* renderer);
    void LoadSoundAssets();
    void LoadMusicAssets();


private:

    std::string m_sManifestFilepath;
    std::string m_sTextureDirectorypath;
    std::string m_sFontsDirectorypath;
    std::string m_sSoundsDirectorypath;

};

extern AssetManager g_AssetManager;
}