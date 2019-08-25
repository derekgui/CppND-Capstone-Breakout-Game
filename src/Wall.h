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

struct BrokenCounter
{
    int yellow;
    int green;
    int orange;
    int red;
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
    BrokenCounter &getBrokenBricks();

private:
    static constexpr int brickWidth = BaseBlock::baseBlockWidth * 2;
    static constexpr int brickHeight = BaseBlock::baseBlockHeight;
    std::ifstream m_inf;
    std::unordered_map<int, BaseBlock> m_bricks;
    BrokenCounter brokenCounter{0, 0, 0, 0};

    void countBrokenBricks(const BaseBlock &brick);
};

#endif