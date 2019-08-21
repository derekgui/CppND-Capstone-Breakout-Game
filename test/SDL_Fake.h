#ifndef SDL_FAKE_H
#define SDL_FAKE_H

#include "ModuleMocks.h"
#include "gmock/gmock.h"

namespace ProjectMocks
{

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

} // namespace ProjectMocks
#endif