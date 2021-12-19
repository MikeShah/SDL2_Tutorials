#include "Collider2D.hpp"

Collider2D::Collider2D()
{
    m_colliderRectangle = new SDL_Rect;
    m_colliderRectangle->x = 0;
    m_colliderRectangle->y = 0;
    m_colliderRectangle->w = 0;
    m_colliderRectangle->h = 0; 
}


Collider2D::~Collider2D(){

}

SDL_Rect& Collider2D::GetColliderBoundingBox() {
    return *m_colliderRectangle;
}

// Detect collision
SDL_bool Collider2D::IsColliding(Collider2D& collider)
{

    if(m_colliderRectangle==nullptr){
        return SDL_FALSE;
    }
    const SDL_Rect* temp = collider.m_colliderRectangle;
    if(temp==nullptr){
        return SDL_FALSE;
    }
    return SDL_HasIntersection(m_colliderRectangle,temp);
}

void Collider2D::SetAbsolutePosition(int x, int y){
    m_colliderRectangle->x = x;
    m_colliderRectangle->y = y;
}
void Collider2D::SetDimensions(int w, int h){
    m_colliderRectangle->w = w;
    m_colliderRectangle->h = h; 
}

#include <iostream>
Vector2D Collider2D::SetBoundingBoxAutomatically(SDL_Surface* surface, int r, int g, int b){
    
    SDL_LockSurface(surface);
    int w= surface->w;
    int h= surface->h;
    int pitch = surface->pitch;
    int colorchannels = pitch/w;  // typically 3 or 4 
    // Important to get the correct pixel type here
    Uint8* pixels = (Uint8*)surface->pixels; 
    
//    std::cout << "w: " << w << std::endl;
//    std::cout << "h: " << h << std::endl;
//    std::cout << "pitch: " << pitch << std::endl;
//    std::cout << "colorchannels: " << colorchannels << std::endl;
//    std::cout << SDL_GetPixelFormatName(surface->format->format) << std::endl;

    SDL_UnlockSurface(surface);
    

    // Set to values larger than an image size
    int xmin=9999999; // Smallest value in x-axis not part of color key
    int xmax=-9999; // Largest value in x-axis not part of color key
    int ymin=9999999;
    int ymax=-9999;

    // Here we're trying to find the 
    // smallest and largest values that are not pink
    // in each of the x and y axis.
    for(int y =0; y < h; y++){
        for(int x=0; x < w; x+=colorchannels){ 

            if(pixels[y*w+x+0] == b &&
               pixels[y*w+x+1] == g &&
               pixels[y*w+x+2] == r){
                // must be transparent
              //  std::cout << "Found a transparent pixel" << std::endl;
                
            }else{
                // Update the smallest and largest
                // values of non-transparent pixels
                xmin = std::min(xmin,x);
                xmax = std::max(xmax,x);

                ymin = std::min(ymin,y);
                ymax = std::max(ymax,y);
            }
        }
    }

    // Update our bounding box
    // Note that the max will always be greater than
    // the minimum value
    //
    m_colliderRectangle->w = (xmax/3 - xmin/3);
    m_colliderRectangle->h = (ymax - ymin);
    //m_colliderRectangle->x = xmin;
    //m_colliderRectangle->y = ymin;

    std::cout << "m_col.w: " << m_colliderRectangle->w << std::endl;
    std::cout << "m_col.h: " << m_colliderRectangle->h << std::endl;
    std::cout << "xmin: " << xmin << std::endl;
    std::cout << "xmax: " << xmax << std::endl;
    std::cout << "ymin: " << ymin << std::endl;
    std::cout << "ymax: " << ymax << std::endl;

    Vector2D result;
    result.x = 35;
    result.y = 45;
    return result;
}

void Collider2D::Update(){
    // not really needed...
}
void Collider2D::Render(){

}
