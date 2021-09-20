// On linux compile with:
// g++ -std=c++17 main.cpp -o prog -lSDL2 -ldl
// On windows compile with (if using mingw)
// g++ main.cpp -o prog.exe -lmingw32 -lSDL2main -lSDL2

// C++ Standard Libraries
#include <iostream>
// Third Party
#include <SDL2/SDL.h>

int main(int argc, char* argv[]){
    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=nullptr;

    // Grab the window surface.
    SDL_Surface* screen;

    // Initialize the video subsystem.
    // If it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("C++ SDL2 Window",
            20,
            20,
            640,
            480,
            SDL_WINDOW_SHOWN);

    screen = SDL_GetWindowSurface(window);

    SDL_Surface* image;
    image = SDL_LoadBMP("./images/3D-Window_BBB_Blender_2.bmp");
    SDL_BlitSurface(image,NULL,screen,NULL);
    SDL_FreeSurface(image);
    SDL_UpdateWindowSurface(window);

    // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }
            // Handle Mouse motion
            if(event.type == SDL_MOUSEMOTION){
            }
            // Handle key presses
            if(event.type == SDL_KEYDOWN){
            }
            // Handle specific key presses from scancodes
            const Uint8* state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_RIGHT]){
                std::cout << "right arrow key is pressed\n";
            }
        }

    }

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    
    // our program.
    SDL_Quit();
    return 0;
}
