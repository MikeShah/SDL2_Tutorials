#include "Collider2D.hpp"

// TODO: iostream for now for
//       reporting errors. Should
//       log otherwise to separate buffer
#include <iostream>

BoxCollider2D::BoxCollider2D()
{
    m_colliderRectangle = new SDL_Rect;
    m_colliderRectangle->x = 0;
    m_colliderRectangle->y = 0;
    m_colliderRectangle->w = 0;
    m_colliderRectangle->h = 0; 
}


BoxCollider2D::~BoxCollider2D(){

}

SDL_Rect& BoxCollider2D::GetColliderBoundingBox() {
    return *m_colliderRectangle;
}

// Detect collision
SDL_bool BoxCollider2D::IsColliding(BoxCollider2D& collider)
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

void BoxCollider2D::SetAbsolutePosition(int x, int y){
    m_colliderRectangle->x = x;
    m_colliderRectangle->y = y;
}
void BoxCollider2D::SetDimensions(int w, int h){
    m_colliderRectangle->w = w;
    m_colliderRectangle->h = h; 
}

Vector2D BoxCollider2D::SetBoundingBoxAutomatically(SDL_Surface* surface, Uint8 r, Uint8 g, Uint8 b){
    
    if(surface==nullptr){
        std::cerr << "SetBoundingBoxAutomatically: nullptr detected for bounding box surface" << std::endl;
    }
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
    int xmin= w; // Smallest value in x-axis not part of color key
    int xmax= 0; // Largest value in x-axis not part of color key
    int ymin= h;
    int ymax= 0;

    for(int y =0; y < h; y++){
        for(int x=0; x < w*colorchannels; x+=colorchannels){ 

            if(pixels[y*(w*colorchannels)+x+0] == b &&
               pixels[y*(w*colorchannels)+x+1] == g &&
               pixels[y*(w*colorchannels)+x+2] == r){
                // pixel must be transparent
            }else{
                // Update the smallest and largest
                // values of non-transparent pixels
                xmin = std::min(x,xmin);
                xmax = std::max(x,xmax);

                ymin = std::min(ymin,y);
                ymax = std::max(ymax,y);
            }
        }
    }


    // Update our bounding box
    // Note that the max will always be greater than
    // the minimum value
    // For width, we need to divide by the pitch of our object
    int scale = (1200/300);
    m_colliderRectangle->w = ((xmax/colorchannels - xmin/colorchannels)/(scale));
    m_colliderRectangle->h = (ymax - ymin)/scale;
//    m_colliderRectangle->x = m_colliderRectangle->x;
//    m_colliderRectangle->y = m_colliderRectangle->y;

//    std::cout << "m_col.w: " << m_colliderRectangle->w << std::endl;
//    std::cout << "m_col.h: " << m_colliderRectangle->h << std::endl;
//    std::cout << "xmin: " << xmin << std::endl;
//    std::cout << "xmax: " << xmax << std::endl;
//    std::cout << "ymin: " << ymin << std::endl;
//    std::cout << "ymax: " << ymax << std::endl;

    Vector2D result;
    result.x = xmin/(colorchannels*scale);
    result.y = ymin/scale;
    return result;
}

void BoxCollider2D::Update(){
}

void BoxCollider2D::Render(){

}
