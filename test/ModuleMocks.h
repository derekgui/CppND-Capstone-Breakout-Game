#ifndef MODULEMOCKS_H
#define MODULEMOCKS_H
#include "gmock/gmock.h"

namespace ProjectMocks
{

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
    MOCK_METHOD2(SDL_SetWindowTitle, void(SDL_Window *, const char *));
};
} // namespace ProjectMocks

#endif