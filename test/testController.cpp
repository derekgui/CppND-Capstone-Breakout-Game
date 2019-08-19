#include "SDL_Fake.h"

class Controller
{
public:
    enum KEYSTATUS
    {
        LEFT_DOWN,
        RIGHT_DOWN,
        STAT_DEFAULT
    };
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
    bool m_isAvailable{true};
    KEYSTATUS m_keyStatus{STAT_DEFAULT};
    SDL_Event e;
};

class GameController : public TestFixture
{
public:
    Controller controller;
    SDL_Event e;
};

TEST_F(GameController, IsAvailableAfterCreation)
{

    ASSERT_THAT(controller.isAvailable(), Eq(true));
}

TEST_F(GameController, IsNotAvailableWhenQuitEvent)
{
    e.type = SDL_QUIT;

    EXPECT_CALL(*_SDL_Mock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(e), Return(1)))
        .WillOnce(Return(0));

    controller.handleEvent();

    ASSERT_THAT(controller.isAvailable(), Eq(false));
}

TEST_F(GameController, FireLeftKeyFlagwhenPressed)
{
    e.type = SDL_KEYDOWN;
    e.key.keysym.sym = SDLK_LEFT;

    EXPECT_CALL(*_SDL_Mock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(e), Return(1)))
        .WillOnce(Return(0));

    controller.handleEvent();

    ASSERT_THAT(controller.keyStatus(), Eq(controller.LEFT_DOWN));
}

TEST_F(GameController, FireRightKeyFlagwhenPressed)
{
    e.type = SDL_KEYDOWN;
    e.key.keysym.sym = SDLK_RIGHT;

    EXPECT_CALL(*_SDL_Mock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(e), Return(1)))
        .WillOnce(Return(0));

    controller.handleEvent();

    ASSERT_THAT(controller.keyStatus(), Eq(controller.RIGHT_DOWN));
}