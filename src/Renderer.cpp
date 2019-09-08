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
    m_isActive = false;
}

void Renderer::init(const MainWindow &wnd)
{
    try
    {
        m_renderer = Create_Renderer(wnd.get(), -1, SDL_RENDERER_ACCELERATED);
        if (nullptr == m_renderer)
            throw std::runtime_error(SDL_GetError());
        m_isActive = true;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Rendderer could not be created! SDL Error: "
                  << e.what() << "\n";
    }
}

bool Renderer::isActive() const
{
    return m_isActive;
}

void Renderer::clearScreen()
{
    SDL_SetRenderDrawColor(m_renderer.get(),
                           Colors::Black.GetR(),
                           Colors::Black.GetG(),
                           Colors::Black.GetB(),
                           Colors::Black.GetA());
    SDL_RenderClear(m_renderer.get());
}

void Renderer::updateScreen()
{
    SDL_RenderPresent(m_renderer.get());
}

void Renderer::drawRect(const SDL_Rect *rect, Color c)
{
    SDL_SetRenderDrawColor(m_renderer.get(), c.GetR(), c.GetG(), c.GetB(), c.GetA());
    SDL_RenderFillRect(m_renderer.get(), rect);
}

SDL_Renderer *Renderer::get() const noexcept
{
    return m_renderer.get();
}

std::unique_ptr<SDL_Renderer, sdl_deleter> Renderer::Create_Renderer(SDL_Window *window, int index, Uint32 flags)
{
    return std::unique_ptr<SDL_Renderer, sdl_deleter>(
        SDL_CreateRenderer(window, index, flags),
        sdl_deleter());
}
