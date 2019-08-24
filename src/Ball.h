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
    Ball(SDL_Rect brickBlock, Color c);
    bool checkCollision(const BaseBlock &block);
    const Vel &velocity() const;
    Vel &velocity();
    void update();

private:
    Vel m_vel{5, 5};
    bool isColliding{false};
};

#endif