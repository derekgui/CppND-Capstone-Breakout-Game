#include "gtest/gtest.h"
#include "SDL_Fake.h"
#include <exception>

using ::testing::_;
using ::testing::Eq;
using ::testing::Return;

class SDLInitFailedExpection : public std::exception
{
};

class MainWindow
{
public:
    void init()
    {
        if (SDL_Init(SDL_INIT_VEDIO) < 0)
            throw SDLInitFailedExpection();
        m_isActive = true;
    }

    bool isActive()
    {
        return m_isActive;
    }

private:
    bool m_isActive{false};
};

class MainGameWindow : public TestFixture
{
public:
    MainWindow wnd;
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

TEST_F(MainGameWindow, ThrowInializationFail)
{
    EXPECT_CALL(*_SDL_Mock, SDL_Init(SDL_INIT_VEDIO)).Times(1).WillOnce(Return(-1));

    ASSERT_THROW(wnd.init(), SDLInitFailedExpection);
}

TEST_F(MainGameWindow, IsActiveAfterProperInitialization)
{
    wnd.init();

    ASSERT_THAT(wnd.isActive(), true);
}
