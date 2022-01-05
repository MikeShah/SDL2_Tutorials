#include <string>
// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>

#include "AnimatedSprite.hpp"
#include "ResourceManager.hpp"

// Constructor
AnimatedSprite::AnimatedSprite(SDL_Renderer*& renderer, std::string filepath){
   
    SDL_Surface* retrieveSurface = ResourceManager::GetInstance().GetSurface(filepath);
    m_texture = SDL_CreateTextureFromSurface(renderer,retrieveSurface);
}
// Destructor
AnimatedSprite::~AnimatedSprite(){
    SDL_DestroyTexture(m_texture);
}

void AnimatedSprite::Draw(int x, int y, int w, int h){
    // Create a rectangle
    m_dst.x = x;
    m_dst.y = y;
    m_dst.w = w;
    m_dst.h = h;
}

void AnimatedSprite::PlayFrame(int x,int y, int w, int h, int frame){
    m_src.x = x+w*frame;
    m_src.y = y;
    m_src.w = w;
    m_src.h = h;
}

void AnimatedSprite::Update(){

}

void AnimatedSprite::Render(SDL_Renderer*& renderer){
    SDL_RenderCopy(renderer,m_texture,&m_src,&m_dst);
}
