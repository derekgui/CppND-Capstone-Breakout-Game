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

void Paddle::ClampToScreen()
{
    const int right = m_paddleBlock.x + width;

    if (m_paddleBlock.x < 0)
        m_paddleBlock.x = 0;
    else if (right >= MainWindow::SCREEN_WIDTH)
        m_paddleBlock.x = MainWindow::SCREEN_WIDTH - 1 - width;
}

void Paddle::update(const Controller &ctlr)
{
    if (ctlr.keyStatus() == KEYSTATUS::LEFT_DOWN)
    {
        m_paddleBlock.x -= speed;
    }
    if (ctlr.keyStatus() == KEYSTATUS::RIGHT_DOWN)
    {
        m_paddleBlock.x += speed;
    }
}