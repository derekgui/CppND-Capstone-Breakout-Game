#include "Wall.h"
#include <iostream>

Wall::Wall()
{
    m_inf.open("../src/setting.dat");

    if (!m_inf)
        std::cerr << "Uable to load setting file!\n";
    else
    {
        initBricks();
        m_isLoaded = true;
    }
}

Wall::~Wall()
{
    m_inf.close();
    m_isLoaded = false;
}

bool Wall::isLoaded() const
{
    return m_isLoaded;
}

void Wall::initBricks()
{
    while (m_inf)
    {
        int brickType;
        int brickIndex = 0;
        m_inf >> brickType;

        BaseBlock brick{{(brickIndex % 10) * brickWidth,
                         (brickIndex / 10) * brickHeight,
                         brickWidth,
                         brickHeight},
                        Colors::Black};

        switch (brickType)
        {
        case Broken:
            brick.blockColor() = Colors::Black;
            break;
        case Yellow:
            brick.blockColor() = Colors::Yellow;
            break;
        case Green:
            brick.blockColor() = Colors::Green;
            break;
        case Orange:
            brick.blockColor() = Colors::Orange;
            break;
        case Red:
            brick.blockColor() = Colors::Red;
            break;
        default:
            brick.blockColor() = Colors::Black;
            break;
        }
        m_bricks.emplace(brickIndex, brick);
        brickIndex++;
    }
}

void Wall::drawSelf(Renderer &rnd)
{
    if (m_bricks.empty())
        return;

    for (auto b : m_bricks)
    {
        b.second.drawSelf(rnd);
    }
}

void Wall::update(Ball &ball)
{
    if (m_bricks.empty())
        return;

    for (auto b : m_bricks)
    {
        if (ball.checkCollision(b.second))
            b.second.blockColor() = Colors::Black;
    }
}