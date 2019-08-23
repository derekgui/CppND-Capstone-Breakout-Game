#include "Ball.h"

Ball::Ball(SDL_Rect brickBlock, Color c, bool isFixed)
    : BaseBlock(brickBlock, c, isFixed)
{
}

bool Ball::checkCollision(const BaseBlock &block)
{
    int ball_top = Block().y;
    int ball_bottom = Block().y + Block().h;
    int ball_left = Block().x;
    int ball_right = Block().x + Block().w;

    int block_top = block.Block().y;
    int block_bottom = block.Block().y + block.Block().h;
    int block_left = block.Block().x;
    int block_right = block.Block().x + block.Block().w;

    if (ball_bottom <= block_top)
        return false;
    if (ball_top >= block_bottom)
        return false;
    if (ball_right <= block_left)
        return false;
    if (ball_left >= block_right)
        return false;

    return true;
}

const Vel &Ball::velocity() const
{
    return m_vel;
}

Vel &Ball::velocity()
{
    return m_vel;
}

void Ball::update()
{
    Block().x += m_vel.vx;
    Block().y += m_vel.vy;

    if (Block().x < 0)
    {
        Block().x = 0;
        m_vel.vx = -m_vel.vx;
    }
}