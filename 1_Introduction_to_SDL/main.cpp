// On linux compile with:
// g++ -std=c++17 main.cpp -o prog -lSDL2

// On mac (assuming a brew install of SDL2-- "brew install sdl2" in the command line) you can compile with:
// clang++ main.cpp -I$HOMEBREW_CELLAR/sdl2/2.26.1/include (includes the headers) -L$HOMEBREW_CELLAR/sdl2/2.26.1/lib -lSDL2-2.0.0 (these two include the library)
// "2.26.1" would be replaced by the current version of SDL2 you have installed which can be found in the
// /opt/homebrew/Cellar/sdl2 folder

// C++ Standard Libraries
#include <iostream>

// Third-party library
#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else
    {
        std::cout << "SDL video system is ready to go\n";
    }

    return 0;
}
