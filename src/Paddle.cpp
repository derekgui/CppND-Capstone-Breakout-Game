#include "Paddle.h"
#include "Renderer.h"

Paddle::Paddle(SDL_Rect paddleBlock, Color c, bool isFixed)
    : BaseBlock(paddleBlock, c, isFixed),
      m_size(paddleBlock.w / baseBlockWidth)
{
}

void Paddle::ClampToScreen()
{
    const int right = Block().x + m_size * baseBlockWidth;

    if (Block().x < 0)
        Block().x = 0;
    else if (right >= MainWindow::SCREEN_WIDTH)
        Block().x = MainWindow::SCREEN_WIDTH - 1 - m_size * baseBlockWidth;
}

void Paddle::update(const Controller &ctlr)
{
    if (ctlr.keyStatus() == KEYSTATUS::LEFT_DOWN)
    {
        Block().x -= speed;
    }
    if (ctlr.keyStatus() == KEYSTATUS::RIGHT_DOWN)
    {
        Block().x += speed;
    }
}

void Paddle::shrink()
{
    m_size = (Block().w / baseBlockWidth) / 2;
    Block().w = m_size * baseBlockWidth;
}