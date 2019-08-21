#include "Paddle.h"

Paddle::Paddle(int posX, int posY)
    : m_paddleBlock({posX, posY, width, height})
{
}

SDL_Rect Paddle::getPaddleBlock() const
{
    return m_paddleBlock;
}