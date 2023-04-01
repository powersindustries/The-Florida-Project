#include "SoundManager.h"
#include "AssetManager.h"
#include "Core/Systems/Hash.h"
#include "Core/Managers/SettingsManager.h"

#define DEFAULT_VOLUME 128
#define SOUND_CHANNEL -1

namespace Florida
{


// -------------------------------------------------------
// -------------------------------------------------------
SoundManager g_SoundManager;


// -------------------------------------------------------
// -------------------------------------------------------
SoundManager::SoundManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
SoundManager::~SoundManager()
{
}


// -------------------------------------------------------
// -------------------------------------------------------
void SoundManager::ResetSoundManager()
{
    Mix_HaltMusic();

    int iFXVolume = static_cast<int>(DEFAULT_VOLUME * (Core::g_SettingsManager.GetFXVolumePercentage() * 0.01));
    Mix_Volume(SOUND_CHANNEL, iFXVolume);

    int iMusicVolume = static_cast<int>(DEFAULT_VOLUME * (Core::g_SettingsManager.GetMusicVolumePercentage() * 0.01));
    Mix_VolumeMusic(iMusicVolume);

}


// -------------------------------------------------------
// -------------------------------------------------------
void SoundManager::PlaySoundByID(std::string sSoundID)
{
    uint32_t uiSoundHash = Core::StringToHash32(sSoundID);
    SoundAssetData& currSound = g_AssetManager.m_SoundAssets[uiSoundHash];

    Mix_PlayChannel(SOUND_CHANNEL, currSound.m_SoundEffect, 0);
}


// -------------------------------------------------------
// -------------------------------------------------------
void SoundManager::PlayMusicByID(std::string sMusicID)
{
    if (Mix_PlayingMusic() == 0)
    {
        uint32_t uiMusicHash = Core::StringToHash32(sMusicID);
        MusicAssetData& currMusic = g_AssetManager.m_MusicAssets[uiMusicHash];

        Mix_PlayMusic(currMusic.m_Music, -1);
    }

}


// -------------------------------------------------------
// -------------------------------------------------------
void SoundManager::ResumeMusic()
{
    if (Mix_PausedMusic() == 1)
    {
        Mix_ResumeMusic();
    }
}


// -------------------------------------------------------
// -------------------------------------------------------
void SoundManager::PauseMusic()
{
    Mix_PausedMusic();
}


// -------------------------------------------------------
// -------------------------------------------------------
void SoundManager::StopAllMusic()
{
    Mix_HaltMusic();
}

}