#include "SDLApp.hpp"

#include <iostream>

// Constructor
SDLApp::SDLApp(Uint32 subsystemFlags, const char* title,int x, int y, int w, int h){

    m_width= w;
    m_height= h;

    // Default value
    m_maxFrameRate = 60;

    // Initialize the video subsystem.
    // iF it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(subsystemFlags) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    m_window = SDL_CreateWindow(title,x,y,w,h,SDL_WINDOW_SHOWN);

    m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
}

// Destructor
SDLApp::~SDLApp(){
    // Destroy our m_window
    SDL_DestroyWindow(m_window);
    // Quit our SDL application
    SDL_Quit();
}

// Handle Events
void SDLApp::SetEventCallback(std::function<void(void)> func){
    m_EventCallback = func;
}
// Handle Events
void SDLApp::SetUpdateCallback(std::function<void(void)> func){
    m_UpdateCallback = func;
}

// Handle Render
void SDLApp::SetRenderCallback(std::function<void(void)> func){
    m_RenderCallback = func;
    
}

// Loop our application
void SDLApp::RunLoop(){
    while(m_gameIsRunning){
        Uint32 start = SDL_GetTicks();

        // 
        Uint32 buttons;
        buttons = SDL_GetMouseState(&m_mouseX,&m_mouseY);
        // (1) Handle events first
        // User specifies what to do in the events callback
        m_EventCallback();

        // (2) Then handle any updates
        m_UpdateCallback();
        // (3) Then handle our rendering
        // Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(m_renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_renderer);

        // Do our drawing
        SDL_SetRenderDrawColor(m_renderer,255,255,255,SDL_ALPHA_OPAQUE);
        // What the user specifies to happen during the rendering
        // stage in this callback function
        m_RenderCallback();
        // Finally show what we've drawn
        SDL_RenderPresent(m_renderer);

        // Perform the frame capping step
        Uint32 elapsedTime = SDL_GetTicks() - start;
        if(elapsedTime < m_maxFrameRate){
            SDL_Delay(m_maxFrameRate - elapsedTime);
        }
    }
}

void SDLApp::SetMaxFrameRate(int frameRate){
    m_maxFrameRate = frameRate;
}

SDL_Renderer* SDLApp::GetRenderer() const{
    return m_renderer;
}

int SDLApp::GetMouseX(){
    return m_mouseX;
}
int SDLApp::GetMouseY(){
    return m_mouseY;
}

int SDLApp::GetWindowWidth(){
    return m_width;
}

int SDLApp::GetWindowHeight(){
    return m_height;
}

void SDLApp::StopAppLoop(){
    m_gameIsRunning = false;
}
