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
#include <algorithm>
void Collider2D::SetBoundingBoxAutomatically(SDL_Renderer* renderer,TexturedRectangle& rect){
    
    if(renderer==nullptr){
        return;
    }


    int r = rect.GetRedColorKey();
    int g = rect.GetGreenColorKey();
    int b = rect.GetBlueColorKey();
    std::cout << "red color key: " << r << std::endl;
    std::cout << "green color key: " << g << std::endl;
    std::cout << "blue color key: " << b << std::endl;

    
    Uint32 format;
    int w,h;
    int pitch;
    // Retrieivng the format
    SDL_QueryTexture(rect.GetSDLTexture(),&format,NULL,&w,&h);
    SDL_LockTexture(rect.GetSDLTexture(),
                    rect.GetSDLRectPtr(),
                    nullptr, &pitch);
    SDL_UnlockTexture(rect.GetSDLTexture());


    // Algorithm
    //
    
    // TODO Fix this
    int* pixels = new int[w*h*4]; 

    std::cout << "crash here 1" << std::endl;
    SDL_RenderReadPixels(renderer,
                             rect.GetSDLRectPtr(),
                             format,
                             pixels,
                             pitch);
    std::cout << "crash here 2" << std::endl;
    // TODO
    // Need to refactor off camera
    int bpp; // bits per pixel
    int colorchannels;
    if(format==SDL_PIXELFORMAT_ARGB8888){
        bpp=32;
        colorchannels=4; // col
    }else{
        std::cout << "Mike you need to add more pixel formats\n";
        exit(1);
    }

    // Set to values larger than an image size
    int xmin=9999999; // Smallest value in x-axis not part of color key
    int xmax=0; // Largest value in x-axis not part of color key
    int ymin=9999999;
    int ymax=0;


    for(int y =0; y < h; y++){
        for(int x=0; x < w; x+=colorchannels){
            if(y*w+x > w*h*4){
                std::cout << "crash here" << std::endl;
            }
            if(pixels[y*w+x+1] == r &&
               pixels[y*w+x+2] == g &&
               pixels[y*w+x+3] == b){
                // must be transparent
            }else{
                xmin = std::min(xmin,x);
                xmax = std::max(xmax,x);
                ymin = std::min(ymin,y);
                ymax = std::max(ymax,y);
            }
        }
    }

    // Update our bounding box
    m_colliderRectangle->w = xmax - xmin;
    m_colliderRectangle->h = ymax - ymin;

    std::cout << "PixelFormat Name: " << SDL_GetPixelFormatName(format) << std::endl;
    std::cout << "bpp: " << bpp << std::endl;
    std::cout << "pitch: " << pitch << std::endl;
    std::cout << "w: " << w << std::endl;
    std::cout << "h: " << h << std::endl;                            


    // Clean up our memory
    delete[] pixels;
}

void Collider2D::Update(){
    // not really needed...
}
void Collider2D::Render(){

}
