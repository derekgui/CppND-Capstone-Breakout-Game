#include "Controller.h"

Controller::Controller()
    : m_isAvailable(true),
      m_keyStatus(KEYSTATUS::STAT_DEFAULT) {}

bool Controller::isAvailable() const { return m_isAvailable; }

KEYSTATUS Controller::keyStatus() const { return m_keyStatus; }

void Controller::handleEvent()
{
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
            m_isAvailable = false;
        else if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_LEFT)
                m_keyStatus = KEYSTATUS::LEFT_DOWN;
            else if (e.key.keysym.sym == SDLK_RIGHT)
                m_keyStatus = KEYSTATUS::RIGHT_DOWN;
            else
                m_keyStatus = KEYSTATUS::STAT_DEFAULT;
        }
    }
}