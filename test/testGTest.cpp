#include "gtest/gtest.h"
#include "SDL_Fake.h"
#include <exception>
#include <iostream>

using ::testing::_;
using ::testing::Eq;
using ::testing::Return;

static constexpr int SDL_INIT_VEDIO = 0;
static constexpr int SDL_WINDOW_SHOWN = 1;
static constexpr int SDL_WINDOWPOS_UNDEFINED = 0;
static constexpr int SCREEN_WIDTH = 640;
static constexpr int SCREEN_HEIGHT = 480;

class SDLInitFailedExpection : public std::exception
{
};

class SDLCreateWindowFailedExpection : public std::exception
{
};

class MainWindow
{
public:
    void init()
    {
        if (SDL_Init(SDL_INIT_VEDIO) < 0)
            std::cerr << "SDL could not initialized! SDL_Error: "
                      << SDL_GetError() << "\n";
        else
        {
            m_window = SDL_CreateWindow("Breakout Game",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SCREEN_WIDTH,
                                        SCREEN_HEIGHT,
                                        SDL_WINDOW_SHOWN);
            if (NULL == m_window)
                std::cerr << "Window could not be created! SDL_Error: "
                          << SDL_GetError() << "\n";
            else
                m_isActive = true;
        }
    }

    bool isActive() const { return m_isActive; }
    void destroy()
    {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

private:
    bool m_isActive{false};
    SDL_Window *m_window{NULL};
};

class MainGameWindow : public TestFixture
{
public:
    MainWindow wnd;
    SDL_Window *test_window;
};

TEST_F(MainGameWindow, IsDeactiveByDefaultAfterCreate)
{

    ASSERT_THAT(wnd.isActive(), false);
}

TEST_F(MainGameWindow, InitializeSDLLibrary)
{
    EXPECT_CALL(*_SDL_Mock, SDL_Init(SDL_INIT_VEDIO)).Times(1).WillOnce(Return(0));

    wnd.init();
}

TEST_F(MainGameWindow, GetErrorOnInializationFail)
{
    EXPECT_CALL(*_SDL_Mock, SDL_Init(SDL_INIT_VEDIO)).Times(1).WillOnce(Return(-1));
    EXPECT_CALL(*_SDL_Mock, SDL_GetError()).Times(1).WillOnce(Return("SDL Init Failed."));

    wnd.init();
}

TEST_F(MainGameWindow, QuitSDLWhenDestroy)
{
    EXPECT_CALL(*_SDL_Mock, SDL_Quit()).Times(1);

    wnd.destroy();
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
}

TEST_F(MainGameWindow, DestroySDLWindowWhenDestroy)
{
    EXPECT_CALL(*_SDL_Mock, SDL_DestroyWindow(_)).Times(1);
    wnd.destroy();
}