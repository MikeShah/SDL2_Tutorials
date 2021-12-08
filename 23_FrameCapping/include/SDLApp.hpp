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
        // Set the maximum render rate of each frame
        // This is a frame cap in terms of milliseconds that
        // each iteration of our main loop will not exceed
        void SetMaxFrameRate(int frameRate);
        // Retrive the renderer
        SDL_Renderer* GetRenderer() const;
        // Return mouse positions
        int GetMouseX();
        int GetMouseY();
        // Return the window dimensions
        int GetWindowWidth();
        int GetWindowHeight();
        // Stop the main loop of our application
        void StopAppLoop();

    private:
            // Pointer to our SDL Window
            SDL_Window* m_window=nullptr;
            // Pointer to our SDL renderer
            SDL_Renderer* m_renderer = nullptr;
            // Set the maximum frame cap;
            int m_maxFrameRate;
            // Infinite loop for our application
            bool m_gameIsRunning = true;
            // Store mouse Coordinates by default
            int m_mouseX;
            int m_mouseY;
            // Store width and height of window
            int m_width;
            int m_height;
            // Store our callback functions
            std::function<void(void)> m_EventCallback;
            std::function<void(void)> m_RenderCallback;
};

#endif
