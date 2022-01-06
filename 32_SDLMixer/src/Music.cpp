#include "Music.hpp"

#include <iostream>

Music::Music(std::string musicfilepath){
    // TODO: Could configure some options
    // for our playback.
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
        std::cout << "Audio library not working:" << Mix_GetError() << std::endl;;
    } 

    // Load our music file
    m_music= Mix_LoadMUS(musicfilepath.c_str());
    // TODO: Have error checking here
}

Music::~Music(){
    Mix_FreeMusic(m_music);
}

/// number of times to play the music
/// 0 means 0
/// -1 means plays forever.
void Music::PlayMusic(int loops){
    if(m_music!=nullptr){
        Mix_PlayMusic(m_music, loops );
    }
}

void Music::PauseMusic(){
    Mix_PauseMusic();
}

// A range of 0 to 128
void Music::SetVolume(int volume){
    Mix_VolumeMusic(volume);
}
