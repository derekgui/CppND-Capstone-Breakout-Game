#include "Paddle.h"

Paddle::Paddle(int posX, int posY)
    : m_paddleBlock({posX, posY, width, height})
{
}

SDL_Rect Paddle::getBlock() const
{
    return m_paddleBlock;
}

void Paddle::setBlock(const SDL_Rect &b)
{
    m_paddleBlock.x = b.x;
    m_paddleBlock.y = b.y;
    m_paddleBlock.w = b.w;
    m_paddleBlock.h = b.h;
}

void Paddle::drawSelf(Renderer &rnd) const
{
    rnd.drawRect(&m_paddleBlock, Colors::Red);
}