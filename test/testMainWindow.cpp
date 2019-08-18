
#include "../src/MainWindow.h"
#include "gtest/gtest.h"

class MainGameWindow : public TestFixture
{
public:
    static constexpr int SCREEN_WIDTH = 640;
    static constexpr int SCREEN_HEIGHT = 480;

    MainWindow wnd{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT};
};

TEST_F(MainGameWindow, IsDeactiveByDefaultAfterCreate)
{

    ASSERT_THAT(wnd.isActive(), false);
}

TEST_F(MainGameWindow, InitializeSDLLibrary)
{
    EXPECT_CALL(*_SDL_Mock, SDL_Init(SDL_INIT_VIDEO)).Times(1).WillOnce(Return(0));

    wnd.init();
}

TEST_F(MainGameWindow, GetErrorOnInializationFail)
{
    EXPECT_CALL(*_SDL_Mock, SDL_Init(SDL_INIT_VIDEO)).Times(1).WillOnce(Return(-1));
    EXPECT_CALL(*_SDL_Mock, SDL_GetError()).Times(1).WillOnce(Return("SDL Init Failed."));

    wnd.init();
}

TEST_F(MainGameWindow, QuitSDLWhenDestroy)
{
    EXPECT_CALL(*_SDL_Mock, SDL_Quit()).Times(1);
}

TEST_F(MainGameWindow, CreateSDLWindow)
{

    EXPECT_CALL(*_SDL_Mock, SDL_CreateWindow("Breakout Game",
                                             SDL_WINDOWPOS_UNDEFINED,
                                             SDL_WINDOWPOS_UNDEFINED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT,
                                             SDL_WINDOW_SHOWN))
        .Times(1);

    wnd.init();
}

TEST_F(MainGameWindow, GetErrorOnCreateWindowFailure)
{
    EXPECT_CALL(*_SDL_Mock, SDL_CreateWindow("Breakout Game",
                                             SDL_WINDOWPOS_UNDEFINED,
                                             SDL_WINDOWPOS_UNDEFINED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT,
                                             SDL_WINDOW_SHOWN))
        .Times(1)
        .WillOnce(Return(static_cast<SDL_Window *>(NULL)));
    EXPECT_CALL(*_SDL_Mock, SDL_GetError()).Times(1).WillOnce(Return("SDL Create Window Failed."));

    wnd.init();
}

TEST_F(MainGameWindow, IsActiveAfterProperInitialization)
{
    SDL_Window *test_window = new SDL_Window;

    EXPECT_CALL(*_SDL_Mock, SDL_CreateWindow("Breakout Game",
                                             SDL_WINDOWPOS_UNDEFINED,
                                             SDL_WINDOWPOS_UNDEFINED,
                                             SCREEN_WIDTH,
                                             SCREEN_HEIGHT,
                                             SDL_WINDOW_SHOWN))
        .Times(1)
        .WillOnce(Return(test_window));

    wnd.init();

    ASSERT_THAT(wnd.isActive(), true);
    delete test_window;
}

TEST_F(MainGameWindow, DestroySDLWindowWhenDestroy)
{
    EXPECT_CALL(*_SDL_Mock, SDL_DestroyWindow(_)).Times(1);
}