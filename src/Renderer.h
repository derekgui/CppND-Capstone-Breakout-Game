#ifndef RENDERER_H
#define RENDERER_H

#define SDL_FAKE_ON
#ifdef SDL_FAKE_ON
#include "../test/SDL_Fake.h"
#else
#include "SDL2/SDL.h"
#endif

#include "MainWindow.h"

class Renderer
{
public:
    Renderer(const MainWindow &wnd);
    ~Renderer();
    void init(const MainWindow &wnd);

    bool isActive() const;

    void clearScreen();

    void updateScreen();

    void drawRect(const SDL_Rect *rect,
                  Uint8 r,
                  Uint8 g,
                  Uint8 b,
                  Uint8 a);

private:
    bool m_isActive;
    SDL_Renderer *m_renderer;
};

#endif