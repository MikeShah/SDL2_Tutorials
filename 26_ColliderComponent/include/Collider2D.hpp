#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <SDL2/SDL.h>

#include "TexturedRectangle.hpp"

class Collider2D{
    public:

        Collider2D();
 
        ~Collider2D();

        SDL_Rect& GetColliderBoundingBox();

        // Detect collision
        SDL_bool IsColliding(Collider2D& collider);

        void SetAbsolutePosition(int x, int y);
        void SetDimensions(int w, int h);

        void SetBoundingBoxAutomatically(SDL_Renderer* renderer,TexturedRectangle& rect); 

        void Update();
        void Render();

    private:
        SDL_Rect* m_colliderRectangle;
};



#endif
