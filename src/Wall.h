#ifndef WALL_H
#define WALL_H
#include <fstream>
#include <unordered_map>
#include "BaseBlock.h"

enum BrickType
{
    Black,
    Yellow,
    Green,
    Orange,
    Red
};

class Wall
{
public:
    Wall();
    ~Wall();
    bool isLoaded() const;
    const BaseBlock *getBrick(int brickNumber) const;
    BaseBlock *setBrick(int brickNumber);

private:
    bool m_isLoaded{false};
    std::ifstream inf;
    std::unordered_map<int, BaseBlock *> m_bricks;
};

#endif