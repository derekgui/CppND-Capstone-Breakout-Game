#ifndef CONTROLLER_H
#define CONTROLLER_H

#define SDL_FAKE_ON
#ifdef SDL_FAKE_ON
#include "../test/SDL_Fake.h"
#else
#include "SDL2/SDL.h"
#endif
enum class KEYSTATUS
{
    LEFT_DOWN,
    RIGHT_DOWN,
    STAT_DEFAULT
};

class Controller
{
public:
    Controller();
    bool isAvailable() const;
    Controller(const Controller &controller) = delete;
    Controller &operator=(const Controller &controller) = delete;
    KEYSTATUS keyStatus() const;
    void handleEvent();

private:
    bool m_isAvailable;
    KEYSTATUS m_keyStatus;
    SDL_Event e;
};

#endif