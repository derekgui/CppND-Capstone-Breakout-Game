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
            switch (e.key.keysym.sym)
            {
            case SDLK_LEFT:
                m_keyStatus = KEYSTATUS::LEFT_DOWN;
                break;
            case SDLK_RIGHT:
                m_keyStatus = KEYSTATUS::RIGHT_DOWN;
                break;
            case SDLK_SPACE:
                m_keyStatus = KEYSTATUS::SPACE_DOWN;
                break;
            default:
                m_keyStatus = KEYSTATUS::STAT_DEFAULT;
                break;
            }
        }
    }
}
