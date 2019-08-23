#include "Ball.h"

Ball::Ball(SDL_Rect brickBlock, Color c, bool isFixed)
    : BaseBlock(brickBlock, c, isFixed)
{
}

bool Ball::checkCollision(const BaseBlock &block)
{
}