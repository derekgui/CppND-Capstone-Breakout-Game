#ifndef RENDERER_H
#define RENDERER_H

#include "MainWindow.h"
#include "Colors.h"
#include <memory>

class Renderer
{
public:
    Renderer(const MainWindow &wnd);
    ~Renderer();
    void init(const MainWindow &wnd);

    bool isActive() const;

    void clearScreen();

    void updateScreen();

    void drawRect(const SDL_Rect *rect, Color c);

    std::unique_ptr<SDL_Renderer, sdl_deleter> Create_Renderer(SDL_Window *window, int index, Uint32 flags);

    SDL_Renderer *get() const noexcept;

private:
    bool m_isActive;
    std::unique_ptr<SDL_Renderer, sdl_deleter> m_renderer;
};

#endif