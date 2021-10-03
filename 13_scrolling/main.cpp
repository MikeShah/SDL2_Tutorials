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

    SDL_Surface* surface = SDL_LoadBMP("./images/pool2.bmp");
    // Set the color key after loading the surface, and before the texture
    //SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,0xFF,0,0xFF));

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer,surface);

    SDL_FreeSurface(surface); 

    // Create a rectangle
    SDL_Rect rectangle;
    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = 640;
    rectangle.h = 480;

    SDL_Rect rectangle2;
    rectangle2.x = -639;
    rectangle2.y = 0;
    rectangle2.w = 640;
    rectangle2.h = 480;

    SDL_Rect rectangle3;
    rectangle3.x = 0;
    rectangle3.y = 0;
    rectangle3.w = 640;
    rectangle3.h = 480;

    SDL_Rect rectangle4;
    rectangle4.x = 0;
    rectangle4.y = -480;
    rectangle4.w = 640;
    rectangle4.h = 480;

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
            if(event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button == SDL_BUTTON_LEFT){
                    SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_ADD);
                }
                else if(event.button.button == SDL_BUTTON_MIDDLE){
                    SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_BLEND);
                }
                else if(event.button.button == SDL_BUTTON_RIGHT){
                    SDL_SetTextureBlendMode(texture2,SDL_BLENDMODE_MOD);
                }

            }
        }
        // (2) Handle Updates
        
        // (3) Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer,0,0,0xFF,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);


        int w,h;
        SDL_QueryTexture(texture,NULL,NULL,&w,&h);
        // Little hack here, to slow down simulatin.
        SDL_Delay(20);

// Handle textures scrolling left to right
        rectangle.x++;
        if(rectangle.x > 639){
            rectangle.x = -639;
        }
        rectangle2.x++;
        if(rectangle2.x > 639){
            rectangle2.x = -639;
        }

        rectangle3.y++;
        if(rectangle3.y > 479){
            rectangle3.y = -480;
        }
        rectangle4.y++;
        if(rectangle4.y > 479){
            rectangle4.y = -480;
        }

        // Order matters
        // Scrolling left and right
        SDL_SetTextureBlendMode(texture,SDL_BLENDMODE_NONE);
        SDL_RenderCopy(renderer,texture,NULL,&rectangle);
        SDL_RenderCopy(renderer,texture,NULL,&rectangle2);
        // Scrolling up and down
        SDL_RenderCopy(renderer,texture2,NULL,&rectangle3);
        SDL_RenderCopy(renderer,texture2,NULL,&rectangle4);


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
