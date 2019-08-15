//#include "SDL2/SDL.h"
#include <memory>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

typedef struct SDL_Window SDL_Window;
typedef uint32_t Uint32;

static constexpr int SDL_INIT_VEDIO = 0;

using namespace ::testing;
using ::testing::_;
using ::testing::Eq;
using ::testing::Return;

class SDL_Mock
{
public:
    virtual ~SDL_Mock() {}

    //Mock Methods
    MOCK_METHOD1(SDL_Init, int(Uint32));
    MOCK_METHOD6(SDL_CreateWindow, SDL_Window *(const char *, int, int, int, int, Uint32));
};

class TestFixture : public ::testing::Test
{
public:
    TestFixture() { _SDL_Mock.reset(new NiceMock<SDL_Mock>()); }
    ~TestFixture()
    {
        _SDL_Mock.reset();
    }

    static std::unique_ptr<SDL_Mock> _SDL_Mock;
};

std::unique_ptr<SDL_Mock> TestFixture::_SDL_Mock;

int SDL_Init(Uint32 Flag) { return TestFixture::_SDL_Mock->SDL_Init(Flag); }

class MainWindow
{
public:
    void init()
    {
        SDL_Init(SDL_INIT_VEDIO);
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

TEST_F(MainGameWindow, IsActiveAfterInitialization)
{
    wnd.init();
    ASSERT_THAT(wnd.isActive(), true);
}

TEST_F(MainGameWindow, InitializeSDLLibrary)
{
    EXPECT_CALL(*_SDL_Mock, SDL_Init(SDL_INIT_VEDIO)).Times(1).WillOnce(Return(0));

    wnd.init();
}