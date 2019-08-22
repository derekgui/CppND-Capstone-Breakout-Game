#include "Renderer.h"
#include <iostream>

Renderer::Renderer(const MainWindow &wnd)
    : m_isActive(false),
      m_renderer(nullptr)
{
    init(wnd);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
    m_renderer = nullptr;
    m_isActive = false;
}

void Renderer::init(const MainWindow &wnd)
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

bool Renderer::isActive() const
{
    return m_isActive;
}

void Renderer::clearScreen()
{
    SDL_SetRenderDrawColor(m_renderer,
                           Colors::Black.GetR(),
                           Colors::Black.GetG(),
                           Colors::Black.GetB(),
                           Colors::Black.GetA());
    SDL_RenderClear(m_renderer);
}

void Renderer::updateScreen()
{
    SDL_RenderPresent(m_renderer);
}

void Renderer::drawRect(const SDL_Rect *rect, Color c)
{
    SDL_SetRenderDrawColor(m_renderer, c.GetR(), c.GetG(), c.GetB(), c.GetA());
    SDL_RenderFillRect(m_renderer, rect);
}

SDL_Renderer *Renderer::get() const noexcept
{
    return m_renderer;
}