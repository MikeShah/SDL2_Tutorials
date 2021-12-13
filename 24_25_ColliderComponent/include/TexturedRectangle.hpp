#ifndef TEXTUREDRECTANGLE_HPP
#define TEXTUREDRECTANGLE_HPP

#include <string>
// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>

class TexturedRectangle{
    public:
        // Constructor
        TexturedRectangle(SDL_Renderer* renderer, std::string filepath);
        TexturedRectangle(SDL_Renderer* renderer, std::string filepath, int redcolorkey, int greencolorkey, int bluecolorkey);

        void InitDefaults();
        // Destructor
        ~TexturedRectangle();
        // 
        void SetPosition(int x, int y);
        int GetPositionX();
        int GetPositionY();
        void SetDimensions(int w, int h);
        int GetWidth();
        int GetHeight();
        // Copy Constructor..
        // Copy assignment operator

        // Update every frame
        void Update();
        // Render
        void Render(SDL_Renderer* renderer);
    private:
        inline SDL_Rect GetRectangle() const { return m_rectangle; }

        SDL_Rect m_rectangle;
        SDL_Texture* m_texture;

        int m_redColorKey;
        int m_greenColorKey;
        int m_blueColorKey;
};


#endif
