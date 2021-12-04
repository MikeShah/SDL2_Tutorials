// On linux compile with:
// g++ -std=c++17 main.cpp -o prog -lSDL2 -lSDL2_image -ldl

// C++ Standard Libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "SDLApp.hpp"
#include "TexturedRectangle.hpp"
#include "AnimatedSprite.hpp"

// One possibility of creating as a global our app
SDLApp* app;

// Create two objects to render
// Eventually, we will want some sort of factory
// to manage object creation in our App...
TexturedRectangle* object1;
TexturedRectangle* object2;

void HandleEvents(){
    SDL_Event event;

    // (1) Handle Input
    // Start our event loop
    while(SDL_PollEvent(&event)){
        // Handle each specific event
        if(event.type == SDL_QUIT){
            app->StopAppLoop();
        }
        // Detect collision from our two shapes if mouse
        // button is pressed
        if(event.button.button == SDL_BUTTON_LEFT){
           if(object2->IsColliding(*object1)){
                std::cout << "Is colliding" << std::endl;
           }else{
               std::cout << "Not colliding" << std::endl;
           }
        }
    }
}

void HandleRendering(){
    // Set draw positions and size
    object1->Draw(50,50,100,100);
    object2->Draw(app->GetMouseX(),app->GetMouseY(),100,100);
    
    // Render our objects
    object1->Render(app->GetRenderer());
    object2->Render(app->GetRenderer());
}


int main(int argc, char* argv[]){
    // Setup the SDLApp
    const char* title = "New SDL2 Abstraction";
    app = new SDLApp(title, 20,20,640,480);

    // Create any objects in our scene
    object1 = new TexturedRectangle(app->GetRenderer(),"./images/test.bmp");
    object2 = new TexturedRectangle(app->GetRenderer(),"./images/test.bmp");
    // Set callback functions
    app->SetEventCallback(HandleEvents);
    app->SetRenderCallback(HandleRendering);
    // Run our application until terminated
    app->RunLoop();

    // Clean up our application
    delete app;
    delete object1;
    delete object2;

    return 0;
}
