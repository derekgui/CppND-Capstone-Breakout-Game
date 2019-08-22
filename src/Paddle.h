#ifndef PADDLE_H
#define PADDLE_H

#define SDL_FAKE_ON
#ifdef SDL_FAKE_ON
#include "../test/SDL_Fake.h"
#else
#include "SDL2/SDL.h"
#endif
#include "BaseBlock.h"
#include "Controller.h"
#include "Renderer.h"

class Paddle : public BaseBlock
{
public:
    Paddle(SDL_Rect paddleBlock, Color c, bool isFixed);
    void ClampToScreen();
    void update(const Controller &ctlr);
    void shrink();

private:
    int m_size;
    static constexpr float speed = 1;
};

#endif