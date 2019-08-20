#ifndef RENDERER_H
#define RENDERER_H

#define SDL_FAKE_ON
#ifdef SDL_FAKE_ON
#include "../test/SDL_Fake.h"
#else
#include "SDL2/SDL.h"
#endif

#include "../src/MainWindow.h"
#include <iostream>

class Renderer
{
public:
    Renderer(const MainWindow &wnd)
        : m_isActive(false),
          m_renderer(nullptr)
    {
        init(wnd);
    }

    ~Renderer()
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
        m_isActive = false;
    }
    void init(const MainWindow &wnd)
    {
        m_renderer = SDL_CreateRenderer(wnd.get(), -1, SDL_RENDERER_ACCELERATED);
        if (nullptr == m_renderer)
            std::cerr << "Rendderer could not be created! SDL Error: "
                      << SDL_GetError() << "\n";
        else
        {
            m_isActive = true;
        }
    }

    bool isActive() const
    {
        return m_isActive;
    }

    void clearScreen()
    {
        SDL_SetRenderDrawColor(m_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderClear(m_renderer);
    }

    void updateScreen()
    {
        SDL_RenderPresent(m_renderer);
    }

    void drawRect(const SDL_Rect *rect,
                  Uint8 r,
                  Uint8 g,
                  Uint8 b,
                  Uint8 a)
    {
        SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
        SDL_RenderFillRect(m_renderer, rect);
    }

private:
    bool m_isActive;
    SDL_Renderer *m_renderer;
};

#endif