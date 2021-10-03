// On linux compile with:
// g++ -std=c++17 main.cpp -o prog -lSDL2 -ldl
// On windows compile with (if using mingw)
// g++ main.cpp -o prog.exe -lmingw32 -lSDL2main -lSDL2
// On Mac compile with:
// clang++ main.cpp -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2

// C++ Standard Libraries
#include <iostream>
// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>

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

    SDL_Surface* surface = SDL_LoadBMP("./images/kong.bmp");
    // Set the color key after loading the surface, and before the texture
    SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0xFF,0,0xFF));


    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_FreeSurface(surface); 

    // Create a rectangle
    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 100;
    rectangle.w = 200;
    rectangle.h = 200;

    SDL_Rect rectangle2;
    rectangle2.x = 50;
    rectangle2.y = 100;
    rectangle2.w = 200;
    rectangle2.h = 200;


    // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }
            if(event.type == SDL_MOUSEMOTION){
                rectangle2.x = event.motion.x;
                rectangle2.y = event.motion.y;
            }
            if(event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_LEFT){
                    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_ADD);
                }
                else if(event.button.button == SDL_BUTTON_MIDDLE){
                    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_BLEND);
                }
                else if(event.button.button == SDL_BUTTON_RIGHT){
                    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_MOD);
                }

            }
            else{
                    SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_NONE);
            }
        }
        // (2) Handle Updates
        
        // (3) Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Do our drawing
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(renderer,5,5,200,220);

//        SDL_RenderDrawRect(renderer,&rectangle);
        SDL_RenderCopy(renderer,texture,NULL,&rectangle);
        SDL_RenderCopy(renderer,texture,NULL,&rectangle2);


        // Finally show what we've drawn
        SDL_RenderPresent(renderer);

    }

    SDL_DestroyTexture(texture);
    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    
    // our program.
    SDL_Quit();
    return 0;
}
