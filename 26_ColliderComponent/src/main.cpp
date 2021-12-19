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
#include "ResourceManager.hpp"
#include "Vector2D.hpp"

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
           // Check collision between object2 and object 1 collider at first hit box
           if(object2->GetCollider2D(0).IsColliding(object1->GetCollider2D(0))){
                std::cout << "Is colliding with hit box 1" << std::endl;
           }else{
               std::cout << "Not colliding with hit box 1" << std::endl;
           }

           // Check collision between object2 and object 1 collider at second hit box
           if(object2->GetCollider2D(0).IsColliding(object1->GetCollider2D(1))){
                std::cout << "Is colliding with hit box 2" << std::endl;
           }else{
               std::cout << "Not colliding with hit box 2" << std::endl;
           }
        }
    }
}

void HandleUpdate(){
    // Update each of the objects
    object1->Update();
    object2->Update();

    // Set draw positions and size
    object1->GetTexturedRectangle().SetPosition(app->GetMouseX(),app->GetMouseY());
    object1->GetTexturedRectangle().SetDimensions(300,300);

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

    // Update object 2 collider positions and dimensions
    object2->GetCollider2D(0).SetAbsolutePosition(object2->GetTexturedRectangle().GetPositionX(), object2->GetTexturedRectangle().GetPositionY());
    object2->GetCollider2D(0).SetDimensions(object2->GetTexturedRectangle().GetWidth(), object2->GetTexturedRectangle().GetHeight());

    // For each of the objects , update the colliders
    // Update each of object 1's colliders position and dimensions
    object1->GetCollider2D(0).SetAbsolutePosition(object1->GetTexturedRectangle().GetPositionX(), object1->GetTexturedRectangle().GetPositionY());

    object1->GetCollider2D(0).SetDimensions(object2->GetTexturedRectangle().GetWidth(), object1->GetTexturedRectangle().GetHeight()/2);
    object1->GetCollider2D(1).SetAbsolutePosition(object1->GetTexturedRectangle().GetPositionX(), object1->GetTexturedRectangle().GetPositionY()+object1->GetTexturedRectangle().GetHeight()/2);

    object1->GetCollider2D(1).SetDimensions(object1->GetTexturedRectangle().GetWidth(), object1->GetTexturedRectangle().GetHeight()/2);

    Vector2D dims = object1->GetCollider2D(0).SetBoundingBoxAutomatically(ResourceManager::GetInstance().GetSurface("./images/kong.bmp"),0xFF,0x00,0xFF);

    int newXPos = dims.x + app->GetMouseX();
    int newYPos = dims.y/2 + app->GetMouseY();

    object1->GetCollider2D(0).SetAbsolutePosition(newXPos,newYPos);


}

void HandleRendering(){    
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
    object1 = new GameEntity(app->GetRenderer());
    object1->AddTexturedRectangleComponent("./images/kong.bmp", 0xFF, 0x00, 0xFF);
    object1->AddCollider2D();
    object1->AddCollider2D();

    object2 = new GameEntity(app->GetRenderer());
    object2->AddTexturedRectangleComponent("./images/kong.bmp");
    object2->AddCollider2D();

    // Set callback functions
    app->SetEventCallback(HandleEvents);
    app->SetUpdateCallback(HandleUpdate);
    app->SetRenderCallback(HandleRendering);
    // Run our application until terminated
    app->RunLoop();

    // Clean up our application
    delete app;
    delete object1;
    delete object2;

    return 0;
}
