#ifndef WALL_H
#define WALL_H
#include <fstream>
#include <unordered_map>
#include "Ball.h"

enum BrickType
{
    Broken,
    Yellow,
    Green,
    Orange,
    Red,
    TotalTypes
};

class Wall
{
public:
    Wall();
    ~Wall();
    bool isLoaded() const;
    void initBricks();
    void drawSelf(Renderer &rnd);
    void update(Ball &ball);

private:
    static constexpr int brickWidth = BaseBlock::baseBlockWidth * 2;
    static constexpr int brickHeight = BaseBlock::baseBlockHeight;
    std::ifstream m_inf;
    std::unordered_map<int, BaseBlock> m_bricks;
};

#endif