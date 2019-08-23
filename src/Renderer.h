#ifndef RENDERER_H
#define RENDERER_H

#include "MainWindow.h"
#include "Colors.h"

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

    SDL_Renderer *get() const noexcept;

private:
    bool m_isActive;
    SDL_Renderer *m_renderer;
};

#endif