
#include "../src/MainWindow.cpp"

class MainGameWindow : public TestFixture
{
public:
    static constexpr int SCREEN_WIDTH = 640;
    static constexpr int SCREEN_HEIGHT = 640;

    MainWindow wnd{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT};
    std::unique_ptr<SDL_Window> test_window = std::make_unique<SDL_Window>();
    void arrangeWindowCreation(SDL_Window *returnWindowAddress)
    {
        EXPECT_CALL(*_SDL_Mock, SDL_CreateWindow("Breakout Game",
                                                 SDL_WINDOWPOS_UNDEFINED,
                                                 SDL_WINDOWPOS_UNDEFINED,
                                                 SCREEN_WIDTH,
                                                 SCREEN_HEIGHT,
                                                 SDL_WINDOW_SHOWN))
            .Times(1)
            .WillOnce(Return(returnWindowAddress));
    }
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
    arrangeWindowCreation(static_cast<SDL_Window *>(NULL));

    wnd.init();
}

TEST_F(MainGameWindow, GetErrorOnCreateWindowFailure)
{
    EXPECT_CALL(*_SDL_Mock, SDL_GetError()).Times(1).WillOnce(Return("SDL Create Window Failed."));

    arrangeWindowCreation(static_cast<SDL_Window *>(NULL));

    wnd.init();
}

TEST_F(MainGameWindow, IsActiveAfterProperInitialization)
{
    arrangeWindowCreation(test_window.get());

    wnd.init();

    ASSERT_THAT(wnd.isActive(), true);
}

TEST_F(MainGameWindow, ReturnWindowRawPointWhenGet)
{
    arrangeWindowCreation(test_window.get());

    wnd.init();

    ASSERT_THAT(wnd.get(), Eq(test_window.get()));
}

TEST_F(MainGameWindow, DestroySDLWindowWhenDestroy)
{
    EXPECT_CALL(*_SDL_Mock, SDL_DestroyWindow(_)).Times(1);
}

TEST_F(MainGameWindow, DeactiveWindowWhenDestroy)
{

    arrangeWindowCreation(test_window.get());
    wnd.init();
    wnd.destroy();

    ASSERT_THAT(wnd.isActive(), Eq(false));
}

TEST_F(MainGameWindow, UpdateWindowTitle)
{
    EXPECT_CALL(*_SDL_Mock, SDL_SetWindowTitle(_, _)).Times(1);

    int score = 5;
    int fps = 60;

    wnd.UpdateWindowTitle(score, fps);
}