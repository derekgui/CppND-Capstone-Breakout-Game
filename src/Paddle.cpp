#include "Paddle.h"

Paddle::Paddle(SDL_Rect paddleBlock, Color c)
    : BaseBlock(paddleBlock, c),
      m_size(paddleBlock.w / baseBlockWidth)
{
}

void Paddle::ClampToScreen()
{
    const int right = getBlock().x + m_size * baseBlockWidth;

    if (getBlock().x < 0)
        setBlock().x = 0;
    else if (right >= MainWindow::SCREEN_WIDTH)
        setBlock().x = MainWindow::SCREEN_WIDTH - 1 - m_size * baseBlockWidth;
}

void Paddle::update(const Controller &ctlr)
{
    if (ctlr.keyStatus() == KEYSTATUS::LEFT_DOWN)
    {
        setBlock().x -= speed;
    }
    if (ctlr.keyStatus() == KEYSTATUS::RIGHT_DOWN)
    {
        setBlock().x += speed;
    }
}