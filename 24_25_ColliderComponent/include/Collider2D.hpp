#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <SDL2/SDL.h>

class Collider2D{
    public:

        Collider2D();
 
        ~Collider2D();

        SDL_Rect& GetColliderBoundingBox();

        // Detect collision
        SDL_bool IsColliding(Collider2D& collider);

        void SetAbsolutePosition(int x, int y);
        void SetDimensions(int w, int h);

        void Update();
        void Render();

    private:
        SDL_Rect* m_colliderRectangle;
};



#endif
