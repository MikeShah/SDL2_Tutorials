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
#include "Layer.hpp"
#include "GameEntity.hpp"
#include "ResourceManager.hpp"
#include "Vector2D.hpp"
#include "Sound.hpp"
#include "DynamicText.hpp"
#include "Music.hpp"
#include "EntityManager.hpp"

// One possibility of creating as a global our app
SDLApp* app;


Sound* CollisionSound;
Sound* ScoreSound;

Music* MainMusicTrack;

struct GameState{
    float movementSpeed;
    float ballSpeed;
    int ballXDirection;
    int ballYDirection;
    int leftScore;
    int rightScore;
};

// Holds global state of the currently playing game
GameState* gameState;

// Handle the left paddle movement
void HandleLeftPaddle(){
    std::shared_ptr<GameEntity> leftpaddle = EntityManager::GetInstance().GetEntityRef("leftpaddle");

    if(nullptr != leftpaddle){
        int leftpaddlex  =  leftpaddle->GetTexturedRectangle().GetPositionX();
        int leftpaddley  =  leftpaddle->GetTexturedRectangle().GetPositionY();

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_W]){
            leftpaddley -= gameState->movementSpeed;
            leftpaddle->SetPosition(leftpaddlex,leftpaddley);
        }
        else if(state[SDL_SCANCODE_S]){
            leftpaddley += gameState->movementSpeed;
            leftpaddle->SetPosition(leftpaddlex,leftpaddley);
        }
    }
}

// Handle the right paddle movement
void HandleRightPaddle(){
    std::shared_ptr<GameEntity> rightpaddle= EntityManager::GetInstance().GetEntityRef("rightpaddle");

    if(nullptr != rightpaddle){
        int rightpaddlex = rightpaddle->GetTexturedRectangle().GetPositionX();
        int rightpaddley = rightpaddle->GetTexturedRectangle().GetPositionY();

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_UP]) {
            rightpaddley -= gameState->movementSpeed;
            rightpaddle->SetPosition(rightpaddlex,rightpaddley);
        }
        else if (state[SDL_SCANCODE_DOWN]) {
            rightpaddley += gameState->movementSpeed;
            rightpaddle->SetPosition(rightpaddlex,rightpaddley);
        }
    }
}

// Callback function for handling events
void HandleEvents(){
    SDL_Event event;

    // (1) Handle Input
    // Start our event loop
    while(SDL_PollEvent(&event)){
        // Handle each specific event
        if(event.type == SDL_QUIT){
            app->StopAppLoop();
        }
    }
    // Handle paddle movement
    HandleLeftPaddle();
    HandleRightPaddle();
}



// Position the ball in the center of the court
void SetBallPositionCenter(){
    std::shared_ptr<GameEntity> ball = EntityManager::GetInstance().GetEntityRef("ball");

    if(nullptr != ball){
        int ballXposition=app->GetWindowWidth()/2-(ball->GetTexturedRectangle().GetWidth()/2);
        int ballYposition=app->GetWindowHeight()/2-(ball->GetTexturedRectangle().GetHeight()/2);

        // Set the ball position
        ball->SetPosition(ballXposition,ballYposition);
    }
}

// Handle paddle collision
void HandlePaddleCollision(){
    // Grabbing the ball position, and then
    // we will update it based on the direction the ball is traveling
    // Retrieve the created instance
    std::shared_ptr<GameEntity> leftpaddle = EntityManager::GetInstance().GetEntityRef("leftpaddle");
    std::shared_ptr<GameEntity> rightpaddle= EntityManager::GetInstance().GetEntityRef("rightpaddle");
    std::shared_ptr<GameEntity> ball = EntityManager::GetInstance().GetEntityRef("ball");
    int ballXposition = ball->GetTexturedRectangle().GetPositionX();
    int ballYposition = ball->GetTexturedRectangle().GetPositionY();

    // Detection of collision within a paddle
    if(ballXposition >= 20 &&
       gameState->ballXDirection == -1 &&
       leftpaddle->GetBoxCollider2D(0).IsColliding(ball->GetBoxCollider2D(0)))
    { 
        gameState->ballXDirection = 1;
        CollisionSound->PlaySound();
        // Detect where the collision happened
        int paddleMidPoint = leftpaddle->GetTexturedRectangle().GetPositionY()+100;
        if(paddleMidPoint <= ballYposition){
            gameState->ballYDirection = -1; 
        }else if(paddleMidPoint > ballYposition){
            gameState->ballYDirection =  1; 
        }
    }
    else if(ballXposition <=610 && 
            gameState->ballXDirection == 1 &&
            rightpaddle->GetBoxCollider2D(0).IsColliding(ball->GetBoxCollider2D(0)))
    { 
        gameState->ballXDirection = -1;
        CollisionSound->PlaySound();
        // Detect where the collision happened
        int paddleMidPoint = rightpaddle->GetTexturedRectangle().GetPositionY()+100;
        if(paddleMidPoint <= ballYposition){
            gameState->ballYDirection = -1; 
        }else if(paddleMidPoint > ballYposition){
            gameState->ballYDirection = 1; 
        }
    }

    // Set the ball position
    ball->SetPosition(ballXposition,ballYposition);
}

// Handle boundaries along x and y axis of the game board
void HandleBoundariesAndScoring(){
    // Grabbing the ball position, and then
    // we will update it based on the direction the ball is traveling
    std::shared_ptr<GameEntity> ball = EntityManager::GetInstance().GetEntityRef("ball");
    int ballXposition = ball->GetTexturedRectangle().GetPositionX();
    int ballYposition = ball->GetTexturedRectangle().GetPositionY();

    // Set ball boundaries (so we don't fly off the playing field)
    if(ballYposition > app->GetWindowHeight()){
        gameState->ballYDirection = -1;
    }else if(ballYposition < 0){
        gameState->ballYDirection = 1;
    }
    // Set the ball position
    ball->SetPosition(ballXposition,ballYposition);

    // Handle the case of scoring
    // The ball will be centered back to the screen if
    // a score takes place
    if(ballXposition > app->GetWindowWidth() + 80){
        ScoreSound->PlaySound();
        gameState->ballXDirection = -1;
        gameState->leftScore+=1;
        // Recenter ball to start
        SetBallPositionCenter();
    }else if(ballXposition < -100){
        ScoreSound->PlaySound();
        gameState->ballXDirection = 1;
        gameState->rightScore+=1;
        // Recenter ball to start
        SetBallPositionCenter();
    }

}


// Handle the ball moving and it's direction
void HandleBallMoving(){
    // Grabbing the ball position, and then
    // we will update it based on the direction the ball is traveling
    std::shared_ptr<GameEntity> ball = EntityManager::GetInstance().GetEntityRef("ball");
    int ballXposition = ball->GetTexturedRectangle().GetPositionX();
    int ballYposition = ball->GetTexturedRectangle().GetPositionY();
    // Move the ball left-to-right
    if(gameState->ballXDirection == 1 ){
        ballXposition+= gameState->movementSpeed;
    }else{
        ballXposition-= gameState->movementSpeed;
    }
    // Move the ball up-and-down
    if(gameState->ballYDirection == 1 ){
        ballYposition+= gameState->movementSpeed;
    }else{
        ballYposition-= gameState->movementSpeed;
    }

    // Set the ball position
    ball->SetPosition(ballXposition,ballYposition);
}

// Update callback
void HandleUpdate(){
    // Update all of our objects
    EntityManager::GetInstance().UpdateAll();
    // Grabbing the ball position, and then
    // we will update it based on the direction the ball is traveling
    std::shared_ptr<GameEntity> ball = EntityManager::GetInstance().GetEntityRef("ball");
    int ballXposition = ball->GetTexturedRectangle().GetPositionX();
    int ballYposition = ball->GetTexturedRectangle().GetPositionY();
    // Handle Ball Moving
    HandleBallMoving();
    // Handle Boundaries and scoring
    HandleBoundariesAndScoring();
    // Handle Collision with paddles 
    HandlePaddleCollision();
    
    // A bit of a hack, but we want to eventually stop
    // our sounds after some duration.
    static int currentTime   = SDL_GetTicks();
    static int lastTime      = SDL_GetTicks();
    currentTime = SDL_GetTicks();
    if (currentTime > lastTime + 1000) {
        ScoreSound->StopSound();
        CollisionSound->StopSound();
        lastTime = currentTime;
    }
}

// Handle the rendering of the game entities
void HandleRendering(){    
    // Render all of our objects
    EntityManager::GetInstance().RenderAllLayers();

    // Render the text after drawing the objects
    DynamicText leftScore("./assets/fonts/8bitOperatorPlus8-Regular.ttf",32);
    DynamicText rightScore("./assets/fonts/8bitOperatorPlus8-Regular.ttf",32);

    std::string lScore = "left: " + std::to_string(gameState->leftScore);
    std::string rScore= "right: " + std::to_string(gameState->rightScore);

    leftScore.DrawText(app->GetRenderer(),lScore,0,0,100,50);
    rightScore.DrawText(app->GetRenderer(),rScore,500,0,100,50);
}


Uint32 my_callbackfunc(Uint32 interval, void *param){
    std::cout << "Fun score updated from: " << (const char*)param << ":" << gameState->leftScore << " " << gameState->rightScore << std::endl; 

    return 0;
}



// Entry point of the program
int main(int argc, char* argv[]){
    // Setup the SDLApp
    const char* title = "SDL2 Series - Pong";
    app = new SDLApp(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER ,title, 20,20,640,480);
    app->SetMaxFrameRate(16);

    // Create entities
    EntityManager::GetInstance().CreateEntity("court",app->GetRenderer(),LAYER::BACKGROUND);
    EntityManager::GetInstance().CreateEntity("leftpaddle",app->GetRenderer(),LAYER::FOREGROUND);
    EntityManager::GetInstance().CreateEntity("rightpaddle",app->GetRenderer(),LAYER::FOREGROUND);
    EntityManager::GetInstance().CreateEntity("ball",app->GetRenderer(),LAYER::FOREGROUND);

    // Retrieve the created instance
    std::shared_ptr<GameEntity> leftpaddle = EntityManager::GetInstance().GetEntityRef("leftpaddle");
    std::shared_ptr<GameEntity> rightpaddle= EntityManager::GetInstance().GetEntityRef("rightpaddle");
    std::shared_ptr<GameEntity> ball = EntityManager::GetInstance().GetEntityRef("ball");
    std::shared_ptr<GameEntity> court = EntityManager::GetInstance().GetEntityRef("court");
    // Create any objects in our scene
    leftpaddle->AddTexturedRectangleComponent("./assets/images/leftpaddle.bmp");
    leftpaddle->GetTexturedRectangle().SetDimensions(20,200);
    leftpaddle->AddBoxCollider2D();
    leftpaddle->GetBoxCollider2D(0).SetDimensions(leftpaddle->GetTexturedRectangle().GetWidth(), leftpaddle->GetTexturedRectangle().GetHeight());
    leftpaddle->SetPosition(10,200);

    rightpaddle->AddTexturedRectangleComponent("./assets/images/rightpaddle.bmp");
    rightpaddle->GetTexturedRectangle().SetDimensions(20,200);
    rightpaddle->AddBoxCollider2D();
    rightpaddle->GetBoxCollider2D(0).SetDimensions(rightpaddle->GetTexturedRectangle().GetWidth(), rightpaddle->GetTexturedRectangle().GetHeight());
    rightpaddle->SetPosition(610,200);

    ball->AddTexturedRectangleComponent("./assets/images/ball.bmp");
    ball->AddBoxCollider2D();
    ball->GetTexturedRectangle().SetDimensions(20,20);
    ball->GetBoxCollider2D(0).SetDimensions(ball->GetTexturedRectangle().GetWidth(), ball->GetTexturedRectangle().GetHeight());
    ball->SetPosition(app->GetWindowWidth()/2,app->GetWindowHeight()/2);

    court->AddTexturedRectangleComponent("./assets/images/court.bmp");
    court->GetTexturedRectangle().SetDimensions(app->GetWindowWidth(), app->GetWindowHeight());
    court->SetPosition(0,0);

    // Setup our sounds
    CollisionSound = new Sound("./assets/sounds/Collide.wav");
    // TODO: For now, we setup the device 'per sound'
    //       'may' make sense if we have several devices, or
    //       'capture' devices, likely we'll want to refactor
    //       this however.
    CollisionSound->SetupDevice();
    
    // Setupt the score sound
    ScoreSound= new Sound("./assets/sounds/Score.wav");
    ScoreSound->SetupDevice();
    // Setup the music for our game
    MainMusicTrack = new Music("./assets/music/guitarchords.mp3");
    MainMusicTrack->PlayMusic(-1);

    // Setup the Game State
    gameState = new GameState;
    gameState->movementSpeed    = 5.0f;
    gameState->ballSpeed        = 2.0f;
    gameState->ballXDirection   = 1;
    gameState->ballYDirection   = 1;
    gameState->leftScore        = 0;
    gameState->rightScore       = 0;

    // Set callback functions
    app->SetEventCallback(HandleEvents);
    app->SetUpdateCallback(HandleUpdate);
    app->SetRenderCallback(HandleRendering);
    // Add some timers (for demonstration purpose)
    app->AddTimer(2000,my_callbackfunc,(char*)"timer called");
    // Run our application until terminated
    app->RunLoop();

    // Clean up our application
    delete app;
    delete CollisionSound;
    delete ScoreSound;
    // Clean up from our entity manager
    EntityManager::GetInstance().DeleteAllEntities();

    return 0;
}
