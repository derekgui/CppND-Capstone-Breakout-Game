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
    }
}

Wall::~Wall()
{
    m_inf.close();
}

void Wall::initBricks()
{
    int brickType;
    int brickIndex = 0;

    const int posX_offset = 0;
    const int posY_offset = 6;

    while (m_inf)
    {
        m_inf >> brickType;

        BaseBlock brick{{(posX_offset + brickIndex % 20) * brickWidth,
                         (posY_offset + brickIndex / 20) * brickHeight,
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

    auto it = m_bricks.begin();

    while (it != m_bricks.end())
    {
        if (ball.checkCollision(it->second))
            break;
        it++;
    }

    if (it != m_bricks.end())
    {
        countBrokenBricks(it->second);
        m_bricks.erase(it);
    }
}

BrokenCounter &Wall::getBrokenBricks()
{
    return brokenCounter;
}

void Wall::countBrokenBricks(const BaseBlock &brick)
{
    if (brick.blockColor() == Colors::Yellow)
        brokenCounter.yellow++;
    if (brick.blockColor() == Colors::Green)
        brokenCounter.green++;
    if (brick.blockColor() == Colors::Orange)
        brokenCounter.orange++;
    if (brick.blockColor() == Colors::Red)
        brokenCounter.red++;
}