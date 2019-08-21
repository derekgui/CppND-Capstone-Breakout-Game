#include "../src/Controller.cpp"

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

    ASSERT_THAT(controller.keyStatus(), Eq(KEYSTATUS::LEFT_DOWN));
}

TEST_F(GameController, FireRightKeyFlagwhenPressed)
{
    e.type = SDL_KEYDOWN;
    e.key.keysym.sym = SDLK_RIGHT;

    EXPECT_CALL(*_SDL_Mock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(e), Return(1)))
        .WillOnce(Return(0));

    controller.handleEvent();

    ASSERT_THAT(controller.keyStatus(), Eq(KEYSTATUS::RIGHT_DOWN));
}

TEST_F(GameController, FireSpaceBarKeyFlagwhenPressed)
{
    e.type = SDL_KEYDOWN;
    e.key.keysym.sym = SDLK_SPACE;

    EXPECT_CALL(*_SDL_Mock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(e), Return(1)))
        .WillOnce(Return(0));

    controller.handleEvent();

    ASSERT_THAT(controller.keyStatus(), Eq(KEYSTATUS::SPACE_DOWN));
}