#include "Ball.h"

Ball::Ball(SDL_Rect brickBlock, Color c, bool isFixed)
    : BaseBlock(brickBlock, c, isFixed)
{
}

bool Ball::checkCollision(const BaseBlock &block)
{
    int ball_top = getBlock().y;
    int ball_bottom = getBlock().y + getBlock().h;
    int ball_left = getBlock().x;
    int ball_right = getBlock().x + getBlock().w;

    int block_top = block.getBlock().y;
    int block_bottom = block.getBlock().y + block.getBlock().h;
    int block_left = block.getBlock().x;
    int block_right = block.getBlock().x + block.getBlock().w;

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