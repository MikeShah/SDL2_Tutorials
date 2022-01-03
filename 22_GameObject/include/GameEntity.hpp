#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP
#include <string>
// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>

#include "TexturedRectangle.hpp"

class GameEntity{
    public:
      GameEntity(){
        m_sprite = nullptr;
      }
      GameEntity(SDL_Renderer* renderer, std::string spritepath){
        m_renderer = renderer;
        m_sprite = new TexturedRectangle(m_renderer,spritepath);
      }

      ~GameEntity(){
      }

      void Update(){
      }

      void Render(){
        if(nullptr != m_sprite){
            m_sprite->Render(m_renderer);
        }
      }

      TexturedRectangle& GetTexturedRectangle(){
        return *m_sprite;
      }

    private:
      TexturedRectangle* m_sprite; 
      SDL_Renderer* m_renderer;
};


#endif
