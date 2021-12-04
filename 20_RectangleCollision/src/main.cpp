// On linux compile with:
// g++ -std=c++17 main.cpp -o prog -lSDL2 -lSDL2_image -ldl

// C++ Standard Libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>
// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>

#include "TexturedRectangle.hpp"
#include "AnimatedSprite.hpp"

int main(int argc, char* argv[]){
    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=nullptr;

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
    window = SDL_CreateWindow("C++ SDL2 Window",20, 20, 640,480,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    // Create two objects to render
    TexturedRectangle object1(renderer,"./images/test.bmp");
    TexturedRectangle object2(renderer,"./images/test.bmp");

    // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;

        // Variables to store mouse positions
        int mouseX;
        int mouseY;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&mouseX,&mouseY);

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }
            // Detect collision from our two shapes if mouse
            // button is pressed
            if(event.button.button == SDL_BUTTON_LEFT){
               if(object2.IsColliding(object1)){
                    std::cout << "Is colliding" << std::endl;
               }else{
                   std::cout << "Not colliding" << std::endl;
               }

            }
        }
        // (2) Handle Updates
        
        // (3) Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Do our drawing
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);

        // Set draw positions and size
        object1.Draw(50,50,100,100);
        object2.Draw(mouseX,mouseY,100,100);
        
        // Render our objects
        object1.Render(renderer);
        object2.Render(renderer);

        // Finally show what we've drawn
        SDL_RenderPresent(renderer);

        SDL_Delay(100);
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
