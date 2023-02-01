#pragma once
#include <string>

namespace Florida
{

class SoundManager
{
public:
    SoundManager();
    ~SoundManager();

    void ResetSoundManager();
    void PlaySoundByID(std::string sSoundID);
    void PlayMusicByID(std::string sMusicID);
    void ResumeMusic();
    void PauseMusic();
    void StopAllMusic();

};

extern SoundManager g_SoundManager;

}