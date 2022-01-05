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
        // Destructors
        ~GameEntity();
        // Update (called every loop)
        void Update();
        // Render our Game Entity (In the render portion)
        void Render();
        // Adding Rectangle Components
        void AddTexturedRectangleComponent(std::string spritepath);
        // Adding a Rectangle component with transparency
        void AddTexturedRectangleComponent(std::string spritepath, int redcolorkey, int greencolorkey, int bluecolorkey);
        // Add another Box Collider to our object
        void AddBoxCollider2D();
        // Retrieve Components
        TexturedRectangle& GetTexturedRectangle();
        BoxCollider2D& GetBoxCollider2D(size_t index);
        // Update
        // Note: Sets the position of our game entity
        //       This operates by moving all of the
        //       Components position as well so they are
        //       updated.   
        void SetPosition(int x, int y); 
        // Sets all of the components to a specified dimension
        void SetDimensions(int w, int h); 

    private:
        // Components
        TexturedRectangle* m_sprite; 
        std::vector<BoxCollider2D*> m_colliders;
        // Pointer to the renderer that object will render
        // components to.
        SDL_Renderer* m_renderer;
};


#endif
