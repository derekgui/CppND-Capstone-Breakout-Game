#include "SDL2/SDL.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
using namespace ::testing;
using ::testing::Eq;
using ::testing::Return;

class MainWindow
{
public:
    void init()
    {
        m_isActive = true;
    }

    bool isActive()
    {
        return m_isActive;
    }

private:
    bool m_isActive{false};
};

class MainGameWindow : public testing::Test
{
public:
    MainWindow wnd;
};

TEST_F(MainGameWindow, IsDeactiveByDefaultAfterCreate)
{

    ASSERT_THAT(wnd.isActive(), false);
}

TEST_F(MainGameWindow, IsActiveAfterInitialization)
{
    wnd.init();
    ASSERT_THAT(wnd.isActive(), true);
}
