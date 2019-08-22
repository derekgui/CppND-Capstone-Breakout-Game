#include "BaseBlock.h"

BaseBlock::BaseBlock(SDL_Rect block, Color c, bool isFixed)
    : m_block(block),
      m_color(c),
      m_isFixed(isFixed)
{
}

const SDL_Rect &BaseBlock::getBlock() const
{
    return m_block;
}

SDL_Rect &BaseBlock::setBlock()
{
    return m_block;
}

void BaseBlock::drawSelf(Renderer &rnd) const
{
    rnd.drawRect(&m_block, m_color);
}

bool BaseBlock::isFixed() const
{
    return m_isFixed;
}