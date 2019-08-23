#include "BaseBlock.h"

BaseBlock::BaseBlock(SDL_Rect block, Color c)
    : m_block(block),
      m_color(c)
{
}

const SDL_Rect &BaseBlock::Block() const
{
    return m_block;
}

SDL_Rect &BaseBlock::Block()
{
    return m_block;
}

void BaseBlock::drawSelf(Renderer &rnd) const
{
    rnd.drawRect(&m_block, m_color);
}

const Color &BaseBlock::blockColor() const
{
    return m_color;
}

Color &BaseBlock::blockColor()
{
    return m_color;
}