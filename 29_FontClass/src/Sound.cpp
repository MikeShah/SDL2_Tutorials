#include "Sound.hpp"

// For error output
#include <iostream>

Sound::Sound(std::string filepath){
    if(SDL_LoadWAV(filepath.c_str(), &m_audioSpec, &m_waveStart, &m_waveLength) == nullptr){
        std::cerr << "sound loading error: " << SDL_GetError() << std::endl;
    }
}

Sound::~Sound(){
    SDL_FreeWAV(m_waveStart);
    SDL_CloseAudioDevice(m_device);
}

void Sound::PlaySound(){
    // Queue the audio (so we play when available,
    //                  as oppososed to a callback function)
    int status = SDL_QueueAudio(m_device, m_waveStart, m_waveLength);
    SDL_PauseAudioDevice(m_device,0);
}

void Sound::StopSound(){
    SDL_PauseAudioDevice(m_device,1);
}

void Sound::SetupDevice(){
    // Request the most reasonable default device
    // Set the device for playback for 0, or '1' for recording.
    m_device = SDL_OpenAudioDevice(nullptr, 0, &m_audioSpec, nullptr, SDL_AUDIO_ALLOW_ANY_CHANGE);
    // Error message if no suitable device is found to play
    // audio on.
    if(0 == m_device){
        std::cerr << "sound device error: " << SDL_GetError() << std::endl; 
    }
}

