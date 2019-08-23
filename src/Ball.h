#ifndef BALL_H
#define BALL_H
#include "BaseBlock.h"

struct Vel
{
    int vx;
    int vy;
};

class Ball : public BaseBlock
{
public:
    Ball(SDL_Rect brickBlock, Color c, bool isFixed);
    bool checkCollision(const BaseBlock &block);
    const Vel &velocity() const;
    Vel &velocity();

private:
    Vel m_vel{0, 0};
};

#endif