#ifndef PADDLE_H
#define PADDLE_H

#include "BaseBlock.h"
#include "Controller.h"

class Paddle : public BaseBlock
{
public:
    Paddle(SDL_Rect paddleBlock, Color c, bool isFixed);
    void ClampToScreen();
    void update(const Controller &ctlr);
    void shrink();

private:
    int m_size;
    static constexpr float speed = 1;
};

#endif