#ifndef SDL_FAKE_H
#define SDL_FAKE_H
#include <memory>
#include "gmock/gmock.h"

using namespace ::testing;

typedef struct SDL_Window SDL_Window;
typedef uint32_t Uint32;

static constexpr int SDL_INIT_VEDIO = 0;

class SDL_Mock
{
public:
    virtual ~SDL_Mock() {}

    //Mock Methods
    MOCK_METHOD1(SDL_Init, int(Uint32));
    MOCK_METHOD0(SDL_Quit, void(void));
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

//Fack SDL functions
int SDL_Init(Uint32 Flag) { return TestFixture::_SDL_Mock->SDL_Init(Flag); }
void SDL_Quit() { return TestFixture::_SDL_Mock->SDL_Quit(); }
SDL_Window *SDL_CreateWindow(const char *title,
                             int x,
                             int y,
                             int w,
                             int h,
                             Uint32 flags)
{
    return TestFixture::_SDL_Mock->SDL_CreateWindow(title, x, y, w, h, flags);
}

#endif