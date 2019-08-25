#ifndef FRAMETIMER_H
#define FRAMETIMER_H

#include "SDL2/SDL.h"
#include <chrono>

class FrameTimer
{
public:
    FrameTimer();
    Uint32 Mark();

private:
    Uint32 now;
};

#endif