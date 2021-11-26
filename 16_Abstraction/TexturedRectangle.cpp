#include <string>
// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>

#include "TexturedRectangle.hpp"

// Constructor
TexturedRectangle::TexturedRectangle(SDL_Renderer*& renderer, std::string filepath){
    SDL_Surface* surface = SDL_LoadBMP(filepath.c_str());
    m_texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface); 
}
// Destructor
TexturedRectangle::~TexturedRectangle(){
    SDL_DestroyTexture(m_texture);
}

void TexturedRectangle::SetRectangleProperties(int x, int y, int w, int h){
    // Create a rectangle
    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = w;
    m_rectangle.h = h;
}
// Copy Constructor..
// Copy assignment operator
void TexturedRectangle::Update(){

}

void TexturedRectangle::Render(SDL_Renderer*& renderer){
    SDL_RenderCopy(renderer,m_texture,NULL,&m_rectangle);
}
