#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <SDL2/SDL.h>

#include "TexturedRectangle.hpp"
#include "Vector2D.hpp"

class Collider2D{
    public:

        Collider2D();
 
        ~Collider2D();

        SDL_Rect& GetColliderBoundingBox();

        // Detect collision
        SDL_bool IsColliding(Collider2D& collider);

        void SetAbsolutePosition(int x, int y);
        void SetDimensions(int w, int h);

        Vector2D SetBoundingBoxAutomatically(SDL_Surface* surface,Uint8 r, Uint8 g, Uint8 b); 

        void Update();
        void Render();

    private:
        SDL_Rect* m_colliderRectangle;
};



#endif
