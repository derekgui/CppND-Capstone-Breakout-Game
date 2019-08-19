#include "SDL_Fake.h"

class Controller
{
public:
    bool isAvailable() const { return m_isAvailable; }
    void handleEvent()
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                m_isAvailable = false;
        }
    }

private:
    bool m_isAvailable{true};
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