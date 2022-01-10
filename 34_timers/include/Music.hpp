#ifndef MUSIC_HPP
#define MUSIC_HPP

#ifdef MAC
    #include <SDL2_mixer/SDL_mixer.h>
#else
    #include <SDL2/SDL_mixer.h>
#endif

#include <string>

class Music{
    public:
        // Constructor
        Music(std::string musicfilepath);
        // Destructor
        ~Music();

		/// number of times to play the music
		/// 0 means 0
		/// -1 means plays forever.
		void PlayMusic(int loops);
        // Pause the music
		void PauseMusic();
		// A range of 0 to 128
		void SetVolume(int volume);
	private:
		Mix_Music* m_music;
};


#endif
