#ifndef CONTROLLER_H
#define CONTROLLER_H

#define SDL_FAKE_ON
#ifdef SDL_FAKE_ON
#include "../test/SDL_Fake.h"
#else
#include "SDL2/SDL.h"
#endif

class Controller
{
public:
    enum KEYSTATUS
    {
        LEFT_DOWN,
        RIGHT_DOWN,
        STAT_DEFAULT
    };

public:
    Controller()
        : m_isAvailable(true),
          m_keyStatus(STAT_DEFAULT) {}
    Controller(const Controller &controller) = delete;
    Controller &operator=(const Controller &controller) = delete;
    ~Controller() = delete;
    bool isAvailable() const { return m_isAvailable; }
    KEYSTATUS keyStatus() const { return m_keyStatus; }
    void handleEvent()
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                m_isAvailable = false;
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_LEFT)
                    m_keyStatus = LEFT_DOWN;
                else if (e.key.keysym.sym == SDLK_RIGHT)
                    m_keyStatus = RIGHT_DOWN;
                else
                    m_keyStatus = STAT_DEFAULT;
            }
        }
    }

private:
    bool m_isAvailable;
    KEYSTATUS m_keyStatus;
    SDL_Event e;
};

#endif