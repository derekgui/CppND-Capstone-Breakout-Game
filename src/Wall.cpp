#include "Wall.h"
#include <iostream>

Wall::Wall()
{
    inf.open("../src/setting.dat");

    if (!inf)
        std::cerr << "Uable to load setting file!\n";
    else
    {
        m_isLoaded = true;
    }
}

Wall::~Wall()
{
    inf.close();
    m_isLoaded = false;
}

bool Wall::isLoaded() const
{
    return m_isLoaded;
}
