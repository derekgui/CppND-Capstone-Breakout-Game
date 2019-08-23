#include "Ball.h"

Ball::Ball(SDL_Rect brickBlock, Color c)
    : BaseBlock(brickBlock, c)
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

    isColliding = true;

    return isColliding;
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

    const int right = Block().x + Block().w;

    if (Block().x < 0)
    {
        Block().x = 0;
        m_vel.vx = -m_vel.vx;
    }
    else if (right >= MainWindow::SCREEN_WIDTH)
    {
        Block().x = MainWindow::SCREEN_WIDTH - 1 - Block().w;
        m_vel.vx = -m_vel.vx;
    }

    const int bottom = Block().y + Block().h;
    if (Block().y < 0)
    {
        Block().y = 0;
        m_vel.vy = -m_vel.vy;
    }
    else if (bottom >= MainWindow::SCREEN_HEIGHT)
    {
        Block().y = MainWindow::SCREEN_HEIGHT - 1 - Block().h;
        m_vel.vy = -m_vel.vy;
    }

    if (isColliding)
    {
        m_vel.vy = -m_vel.vy;
        isColliding = false;
    }
}