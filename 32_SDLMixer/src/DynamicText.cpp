#include "DynamicText.hpp"
#include <iostream>

// Initialize Static variables
// Should be initialized to false by default
bool DynamicText::s_ttfInitialized = false;

// Constructor
// example: "./assets/fonts/8bitOperatorPlus8-Regular.ttf"
DynamicText::DynamicText(std::string fontfilepath, size_t fontSize){
    // Just like when we initialize our graphics subsystem,
    // we need to do the same for our font system.         	
    if(!s_ttfInitialized && TTF_Init() == -1){
        std::cout << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << std::endl;
    }else if(!s_ttfInitialized){
        std::cout << "SDL2_ttf system ready to go!" << std::endl;
        // Initialize TTF system only once, even if
        // we have multipl Text objects.
        s_ttfInitialized = true;
    }  
    // Load our font file and set the font size
    m_ourFont = TTF_OpenFont(fontfilepath.c_str(),fontSize);
    // Confirm that it was loaded
    if(m_ourFont == nullptr){
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }
}

DynamicText::~DynamicText(){
    // Destroy our textured text
    SDL_DestroyTexture(m_texture);

    // Close our font subsystem
    TTF_CloseFont(m_ourFont);	
}

void DynamicText::DrawText(SDL_Renderer* renderer, std::string text,int x, int y, int w, int h){
    // Pixels from our text
    m_surface = TTF_RenderText_Solid(m_ourFont,text.c_str(),{255,255,255});

    // Setup the texture
    m_texture = SDL_CreateTextureFromSurface(renderer,m_surface);
    // Free the surface
    // We are done with it after we have uploaded to
    // the texture
    SDL_FreeSurface(m_surface);

    // Create a rectangle to draw on
    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = w;
    m_rectangle.h = h;
    // Render our text on a rectangle
    SDL_RenderCopy(renderer,m_texture,NULL,&m_rectangle);

}
