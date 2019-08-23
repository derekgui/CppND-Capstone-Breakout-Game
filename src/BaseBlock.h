#ifndef BaseBlock_H
#define BaseBlock_H

#define SDL_FAKE_ON
#ifdef SDL_FAKE_ON
#include "../test/SDL_Fake.h"
#else
#include "SDL2/SDL.h"
#endif

#include "Renderer.h"

class BaseBlock
{
public:
    BaseBlock(SDL_Rect block, Color c);
    const SDL_Rect &Block() const;
    SDL_Rect &Block();
    void drawSelf(Renderer &rnd) const;
    bool isFixed() const;
    const Color &getColor() const;

protected:
    static constexpr int baseBlockWidth = 32;
    static constexpr int baseBlockHeight = 32;

private:
    SDL_Rect m_block;
    Color m_color;
};

#endif