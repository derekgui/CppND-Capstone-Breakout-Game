#include "SDL_Fake.h"

//Fack SDL functions
int SDL_Init(Uint32 Flag) { return TestFixture::_SDL_Mock->SDL_Init(Flag); }
void SDL_Quit() { return TestFixture::_SDL_Mock->SDL_Quit(); }
const char *SDL_GetError() { return TestFixture::_SDL_Mock->SDL_GetError(); }
SDL_Window *SDL_CreateWindow(const char *title,
                             int x,
                             int y,
                             int w,
                             int h,
                             Uint32 flags)
{
    return TestFixture::_SDL_Mock->SDL_CreateWindow(title, x, y, w, h, flags);
}

void SDL_DestroyWindow(SDL_Window *window)
{
    return TestFixture::_SDL_Mock->SDL_DestroyWindow(window);
}

int SDL_PollEvent(SDL_Event *event)
{
    return TestFixture::_SDL_Mock->SDL_PollEvent(event);
}

SDL_Renderer *SDL_CreateRenderer(SDL_Window *window, int index, Uint32 flags)
{
    return TestFixture::_SDL_Mock->SDL_CreateRenderer(window, index, flags);
}

void SDL_DestroyRenderer(SDL_Renderer *renderer)
{
    return TestFixture::_SDL_Mock->SDL_DestroyRenderer(renderer);
}

int SDL_SetRenderDrawColor(SDL_Renderer *renderer,
                           Uint8 r,
                           Uint8 g,
                           Uint8 b,
                           Uint8 a)
{
    return TestFixture::_SDL_Mock->SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

int SDL_RenderClear(SDL_Renderer *renderer)
{
    return TestFixture::_SDL_Mock->SDL_RenderClear(renderer);
}

void SDL_RenderPresent(SDL_Renderer *renderer)
{
    return TestFixture::_SDL_Mock->SDL_RenderPresent(renderer);
}

int SDL_RenderFillRect(SDL_Renderer *renderer,
                       const SDL_Rect *rect)
{
    return TestFixture::_SDL_Mock->SDL_RenderFillRect(renderer, rect);
}

void SDL_SetWindowTitle(SDL_Window *window,
                        const char *title)
{
    return TestFixture::_SDL_Mock->SDL_SetWindowTitle(window, title);
}