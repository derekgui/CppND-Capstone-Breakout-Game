#ifndef BALL_H
#define BALL_H
#include "BaseBlock.h"

class Ball : public BaseBlock
{
public:
    Ball(SDL_Rect brickBlock, Color c, bool isFixed);
    bool checkCollision(const BaseBlock &block);

private:
};

#endif