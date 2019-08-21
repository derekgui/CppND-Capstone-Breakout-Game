#include "Paddle.h"

void Paddle::init(int posX, int posY)
{
    m_isActive = true;
}

bool Paddle::isActive() const { return m_isActive; }

SDL_Rect Paddle::getPaddleBlock() const
{
    return {0, 0, 32 * 6, 32 * 6};
}