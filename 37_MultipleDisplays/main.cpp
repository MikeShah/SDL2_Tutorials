// On linux compile with:
// g++ -std=c++17 main.cpp -o prog -lSDL2

// C++ Standard Libraries
#include <iostream>

// Third-party library
#include <SDL2/SDL.h>

int main(int argc, char* argv[]){

    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=nullptr;

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
            0,
            2500,
            640,
            480,
            SDL_WINDOW_SHOWN);

    // Handling multiple displays!
    int totalDisplays = SDL_GetNumVideoDisplays();
    SDL_Rect displayDimensions[totalDisplays];

    // Populate our display dimensions
    for(int i=0; i< totalDisplays; i++){
        SDL_GetDisplayBounds(i,&displayDimensions[i]);
        std::cout << "Display " << i << " | " 
                                << displayDimensions[i].x << "," 
                                << displayDimensions[i].y << "," 
                                << displayDimensions[i].w << "," 
                                << displayDimensions[i].h 
                                << std::endl; 
    }
    // Grab a handle to our window, and figure out which display
    // our window is currently on.
    int windowHandle = SDL_GetWindowID(window);
    int numberOfDisplays = SDL_GetWindowDisplayIndex(window);

    // Infinite loop for our application
    bool gameIsRunning = true;
    while(gameIsRunning){
        SDL_Event event;
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }
            // Each keypress will position the window
            // on the appropriate display
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_0){
                    std::cout << "Switch to display 0\n";
                    SDL_SetWindowPosition(window,displayDimensions[0].x,displayDimensions[0].y);
                }else if(event.key.keysym.sym == SDLK_1){
                    if(totalDisplays>1){
                        std::cout << "Switch to display 1\n";
                        SDL_SetWindowPosition(window,displayDimensions[1].x,displayDimensions[1].y);
                    }
                }
            }
        }
    }

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    
    // Shut down SDL2.
    SDL_Quit();

    return 0;
}
