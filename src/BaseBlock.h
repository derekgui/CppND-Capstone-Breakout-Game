#ifndef BaseBlock_H
#define BaseBlock_H

#include "Renderer.h"

class BaseBlock
{
public:
    BaseBlock(SDL_Rect block, Color c);
    const SDL_Rect &Block() const;
    SDL_Rect &Block();
    void drawSelf(Renderer &rnd) const;
    bool isFixed() const;
    const Color &blockColor() const;
    Color &blockColor();

public:
    static constexpr int baseBlockWidth = 16;
    static constexpr int baseBlockHeight = 16;

private:
    SDL_Rect m_block;
    Color m_color;
};

#endif