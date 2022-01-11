#include <string>
// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>

#include "TexturedRectangle.hpp"
#include "ResourceManager.hpp"

// Constructor
TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, std::string filepath){
   
    SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filepath);

    SDL_SetColorKey(retrieveSurface, SDL_FALSE, SDL_MapRGB(retrieveSurface->format, 0xFF, 0x00, 0xFF));
    m_texture = SDL_CreateTextureFromSurface(renderer,retrieveSurface);

    InitDefaults();
}

TexturedRectangle::TexturedRectangle(SDL_Renderer* renderer, std::string filepath, int redcolorkey, int greencolorkey, int bluecolorkey){    
   
    SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filepath);

    // Ability to set the color key for our textured surface
    SDL_SetColorKey(retrieveSurface, SDL_TRUE, SDL_MapRGB(retrieveSurface->format, redcolorkey, greencolorkey, bluecolorkey));

    m_texture = SDL_CreateTextureFromSurface(renderer,retrieveSurface);

    InitDefaults();

    m_redColorKey = redcolorkey;
    m_greenColorKey = greencolorkey;
    m_blueColorKey = bluecolorkey;
}

void TexturedRectangle::InitDefaults(){

    m_rectangle.x = 0;
    m_rectangle.y = 0;
    m_rectangle.w = 32;
    m_rectangle.h = 32;

    m_redColorKey = 0xFF;
    m_greenColorKey = 0x00;
    m_blueColorKey = 0xFF;

}


// Destructor
TexturedRectangle::~TexturedRectangle(){
    SDL_DestroyTexture(m_texture);
}

SDL_Rect& TexturedRectangle::GetSDLRect(){
    return m_rectangle;
}
SDL_Rect* TexturedRectangle::GetSDLRectPtr(){
    return &m_rectangle;
}

SDL_Texture* TexturedRectangle::GetSDLTexture(){
    return m_texture;
}

void TexturedRectangle::SetPosition(int x, int y){
    m_rectangle.x = x;
    m_rectangle.y = y;
}

int TexturedRectangle::GetPositionX(){
    return m_rectangle.x;
}
int TexturedRectangle::GetPositionY(){
    return m_rectangle.y;
}

void TexturedRectangle::SetDimensions(int w, int h){
    m_rectangle.w = w;
    m_rectangle.h = h;
}
int TexturedRectangle::GetWidth(){
    return m_rectangle.w;
}
int TexturedRectangle::GetHeight(){
    return m_rectangle.h;
}

int TexturedRectangle::GetRedColorKey(){
    return m_redColorKey;
}
int TexturedRectangle::GetGreenColorKey(){
    return m_greenColorKey;
}
int TexturedRectangle::GetBlueColorKey(){
    return m_blueColorKey;
}
// Copy Constructor..
// Copy assignment operator

void TexturedRectangle::Update(){

}

void TexturedRectangle::Render(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer,m_texture,NULL,&m_rectangle);
}
