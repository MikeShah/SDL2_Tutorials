// On linux compile with:
// g++ -std=c++17 main.cpp -o prog -lSDL2 -ldl
// On windows compile with (if using mingw)
// g++ main.cpp -o prog.exe -lmingw32 -lSDL2main -lSDL2

// C++ Standard Libraries
#include <iostream>
// Third Party
#include <SDL2/SDL.h>

void SetPixel(SDL_Surface* surface, int x, int y, uint8_t r, uint8_t g, uint8_t b){
    
    SDL_LockSurface(surface);
    uint8_t* pixelArray = (uint8_t*)surface->pixels;
    pixelArray[y*surface->pitch +x*surface->format->BytesPerPixel+0] = g;
    pixelArray[y*surface->pitch +x*surface->format->BytesPerPixel+1] = b;
    pixelArray[y*surface->pitch +x*surface->format->BytesPerPixel+2] = r;
    SDL_UnlockSurface(surface);
}


int main(int argc, char* argv[]){
    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=nullptr;

    // Grab the window surface.
    SDL_Surface* screen;

    // Initialize the video subsystem.
    // iF it returns less than 1, then an
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


    // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;

        int x,y;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&x,&y);

        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }
            if(event.button.button == SDL_BUTTON_LEFT){
                std::cout << "left mouse was pressed (" << x << "," << y << ")\n" ;
                SetPixel(screen, x, y, 255, 0, 0);
            }
            if(event.button.button == SDL_BUTTON_RIGHT){
                std::cout << "rightmouse was pressed (" << x << "," << y << ")\n" ;
                SetPixel(screen, x, y, 0, 0, 255);
            }
        }

        SDL_UpdateWindowSurface(window);
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
