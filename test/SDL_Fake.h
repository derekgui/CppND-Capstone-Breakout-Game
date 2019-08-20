#ifndef SDL_FAKE_H
#define SDL_FAKE_H

#include "gmock/gmock.h"
#include <memory>

using namespace ::testing;

using ::testing::_;
using ::testing::Eq;
using ::testing::Return;

enum EvenType
{
    SDL_QUIT,
    SDL_KEYDOWN
};

enum SYM
{
    SDLK_LEFT,
    SDLK_RIGHT
};

typedef struct
{

} SDL_Window;

typedef struct
{

} SDL_Renderer;

typedef struct
{
    int x;
    int y;
    int w;
    int h;
} SDL_Rect;

typedef struct
{
    EvenType type;

    struct KEY
    {
        struct KEYSYM
        {
            SYM sym;

        } keysym;
    } key;

} SDL_Event;
typedef uint32_t Uint32;
typedef uint8_t Uint8;

static constexpr int SDL_INIT_VIDEO = 0;
static constexpr int SDL_WINDOW_SHOWN = 1;
static constexpr int SDL_WINDOWPOS_UNDEFINED = 0;
static constexpr Uint32 SDL_RENDERER_ACCELERATED = 1;

class SDL_Mock
{
public:
    virtual ~SDL_Mock() {}

    //Window Mock Methods
    MOCK_METHOD1(SDL_Init, int(Uint32));
    MOCK_METHOD0(SDL_Quit, void(void));
    MOCK_METHOD0(SDL_GetError, const char *(void));
    MOCK_METHOD6(SDL_CreateWindow, SDL_Window *(const char *, int, int, int, int, Uint32));
    MOCK_METHOD1(SDL_DestroyWindow, void(SDL_Window *));

    //Event Mock Methods
    MOCK_METHOD1(SDL_PollEvent, int(SDL_Event *));

    //Renderer Mock
    MOCK_METHOD3(SDL_CreateRenderer, SDL_Renderer *(SDL_Window *, int, Uint32));
    MOCK_METHOD1(SDL_DestroyRenderer, void(SDL_Renderer *));
    MOCK_METHOD5(SDL_SetRenderDrawColor, int(SDL_Renderer *, Uint8, Uint8, Uint8, Uint8));
    MOCK_METHOD1(SDL_RenderClear, int(SDL_Renderer *));
    MOCK_METHOD1(SDL_RenderPresent, void(SDL_Renderer *));
    MOCK_METHOD2(SDL_RenderFillRect, int(SDL_Renderer *, const SDL_Rect *));
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
const char *SDL_GetError() { return TestFixture::_SDL_Mock->SDL_GetError(); }
SDL_Window *SDL_CreateWindow(const char *title,
                             int x,
                             int y,
                             int w,
                             int h,
                             Uint32 flags)
{
    return TestFixture::_SDL_Mock->SDL_CreateWindow(title, x, y, w, h, flags);
}

void SDL_DestroyWindow(SDL_Window *window)
{
    return TestFixture::_SDL_Mock->SDL_DestroyWindow(window);
}

int SDL_PollEvent(SDL_Event *event)
{
    return TestFixture::_SDL_Mock->SDL_PollEvent(event);
}

SDL_Renderer *SDL_CreateRenderer(SDL_Window *window, int index, Uint32 flags)
{
    return TestFixture::_SDL_Mock->SDL_CreateRenderer(window, index, flags);
}

void SDL_DestroyRenderer(SDL_Renderer *renderer)
{
    return TestFixture::_SDL_Mock->SDL_DestroyRenderer(renderer);
}

int SDL_SetRenderDrawColor(SDL_Renderer *renderer,
                           Uint8 r,
                           Uint8 g,
                           Uint8 b,
                           Uint8 a)
{
    return TestFixture::_SDL_Mock->SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

int SDL_RenderClear(SDL_Renderer *renderer)
{
    return TestFixture::_SDL_Mock->SDL_RenderClear(renderer);
}

void SDL_RenderPresent(SDL_Renderer *renderer)
{
    return TestFixture::_SDL_Mock->SDL_RenderPresent(renderer);
}

int SDL_RenderFillRect(SDL_Renderer *renderer,
                       const SDL_Rect *rect)
{
    return TestFixture::_SDL_Mock->SDL_RenderFillRect(renderer, rect);
}

#endif