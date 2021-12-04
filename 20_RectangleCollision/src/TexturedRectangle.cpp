#include <string>
// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>

#include "TexturedRectangle.hpp"
#include "ResourceManager.hpp"

// Constructor
TexturedRectangle::TexturedRectangle(SDL_Renderer*& renderer, std::string filepath){
   
    SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filepath);
    m_texture = SDL_CreateTextureFromSurface(renderer,retrieveSurface);
}
// Destructor
TexturedRectangle::~TexturedRectangle(){
    SDL_DestroyTexture(m_texture);
}

void TexturedRectangle::Draw(int x, int y, int w, int h){
    // Create a rectangle
    m_rectangle.x = x;
    m_rectangle.y = y;
    m_rectangle.w = w;
    m_rectangle.h = h;
}
// Copy Constructor..
// Copy assignment operator

SDL_bool TexturedRectangle::IsColliding(TexturedRectangle& obj){
    const SDL_Rect temp = obj.GetRectangle();
    return SDL_HasIntersection(&m_rectangle,&temp);
}

void TexturedRectangle::Update(){

}



void TexturedRectangle::Render(SDL_Renderer*& renderer){
    SDL_RenderCopy(renderer,m_texture,NULL,&m_rectangle);
}
