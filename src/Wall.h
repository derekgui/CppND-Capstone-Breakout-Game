#ifndef WALL_H
#define WALL_H

#include "BaseBlock.h"

class Wall
{
public:
    Wall();
    bool isLoaded() const;

private:
    bool m_isLoaded{false};
};

#endif