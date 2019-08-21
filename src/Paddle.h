#ifndef PADDLE_H
#define PADDLE_H

#define SDL_FAKE_ON
#ifdef SDL_FAKE_ON
#include "../test/SDL_Fake.h"
#else
#include "SDL2/SDL.h"
#endif

#include "Renderer.h"

class Paddle
{
public:
    void init(int posX, int posY);
    bool isActive() const;
    SDL_Rect getPaddleBlock() const;
    void drawSelf(Renderer &rnd) const;

private:
    bool m_isActive{false};
    static constexpr int width = 32 * 6;
    static constexpr int height = 32 * 6;
};

#endif