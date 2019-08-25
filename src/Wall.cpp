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
        m_bricks.erase(it);
    }
}