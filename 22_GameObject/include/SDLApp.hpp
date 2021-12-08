#ifndef SDLAPP_HPP
#define SDLAPP_HPP

#include <functional>

// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>

class SDLApp{
    public:
        // Constructor
        SDLApp(const char* title,int x, int y, int w, int h);
        // Destructor
        ~SDLApp();
        // Handle Events
        void SetEventCallback(std::function<void(void)> func);
        // Handle Render
        void SetRenderCallback(std::function<void(void)> func);
        // Loop our application
        void RunLoop();
        // Retrive the renderer
        SDL_Renderer* GetRenderer() const;
        // Return mouse positions
        int GetMouseX();
        int GetMouseY();
        // Stop the main loop of our application
        void StopAppLoop();

    private:
            // Pointer to our SDL Window
            SDL_Window* m_window=nullptr;
            // Pointer to our SDL renderer
            SDL_Renderer* m_renderer = nullptr;
            // Infinite loop for our application
            bool m_gameIsRunning = true;
            // Store mouse Coordinates by default
            int m_mouseX;
            int m_mouseY;
            // Store our callback functions
            std::function<void(void)> m_EventCallback;
            std::function<void(void)> m_RenderCallback;
};

#endif
