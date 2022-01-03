#ifndef GAMEENTITY_HPP
#define GAMEENTITY_HPP

#include <string>
#include <vector>

// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>

#include "TexturedRectangle.hpp"
#include "Collider2D.hpp"

class GameEntity{
    public:
      // Constructors
      GameEntity();
      GameEntity(SDL_Renderer* renderer);
      // Destructtors
      ~GameEntity();
      // Update (called every loop)
      void Update();

      // Render our Game Entity (In the render portion)
      void Render();

      // Adding components
      void AddTexturedRectangleComponent(std::string spritepath);
      void AddTexturedRectangleComponent(std::string spritepath, int redcolorkey, int greencolorkey, int bluecolorkey);

      void AddCollider2D();
      // Retrieve Components
      TexturedRectangle& GetTexturedRectangle();
      Collider2D& GetCollider2D(size_t index);

    private:
      TexturedRectangle* m_sprite; 
      std::vector<Collider2D*> m_colliders;
      SDL_Renderer* m_renderer;
};


#endif
