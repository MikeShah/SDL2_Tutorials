#ifndef SOUND_HPP
#define SOUND_HPP

#include <string>

// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>

// Interface for Audio
class ISound{
    public:
        // Destructor is virtual for our interface
        virtual ~ISound() {};
        // Member functions that should be implemented
        virtual void PlaySound() = 0;
        virtual void StopSound() = 0;
};

class Sound : public ISound{

    public:
        // Constructor
        Sound(std::string filepath);
        // Destructor
        ~Sound();
        // PlaySound
        void PlaySound();
        // Stop the sound
        void StopSound();
        // Specific to SDL_Audio API
        void SetupDevice();

    private: // (private member variables)
        // Device the Sound will play on
        // NOTE: This could be moved to some configuration,
        //       i.e., a higher level 'AudioManager' class
        SDL_AudioDeviceID m_device;

        // Properties of the Wave File that is loaded
        SDL_AudioSpec m_audioSpec;
        Uint8*        m_waveStart;
        Uint32        m_waveLength;
};

#endif
