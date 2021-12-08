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
#include "GameEntity.hpp"

// One possibility of creating as a global our app
SDLApp* app;

// Create two objects to render
// Eventually, we will want some sort of factory
// to manage object creation in our App...
GameEntity* object1;
GameEntity* object2;

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
           if(object2->GetTexturedRectangle().IsColliding(object1->GetTexturedRectangle())){
                std::cout << "Is colliding" << std::endl;
           }else{
               std::cout << "Not colliding" << std::endl;
           }
        }
    }
}

void HandleRendering(){
    // Set draw positions and size
    object1->GetTexturedRectangle().SetPosition(app->GetMouseX(),app->GetMouseY());
    object1->GetTexturedRectangle().SetDimensions(100,100);

    static int posX =0;
    static int posY =0;
    static bool up = true;
    static bool right = true;

    if(up){
        posY--;
    }else{
        posY++;
    }

    if(right){
        posX++;
    }else{
        posX--;
    }
    
    if(posX > app->GetWindowWidth()){
        right = false;
    }else if(posX < 0){
        right = true;
    }

    if(posY < 0){
        up = false;
    }else if(posY > app->GetWindowHeight()){
        up = true;
    }
          


    object2->GetTexturedRectangle().SetPosition(posX,posY);
    object2->GetTexturedRectangle().SetDimensions(100,100);
    
    // Render our objects
    object1->Render();
    object2->Render();
}


int main(int argc, char* argv[]){
    // Setup the SDLApp
    const char* title = "New SDL2 Abstraction";
    app = new SDLApp(title, 20,20,640,480);
    app->SetMaxFrameRate(16);

    // Create any objects in our scene
    object1 = new GameEntity(app->GetRenderer(),"./images/test.bmp");
    object2 = new GameEntity(app->GetRenderer(),"./images/test.bmp");
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
