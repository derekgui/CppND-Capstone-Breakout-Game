#ifndef EXAMPLE_H
#define EXAMPLE_H

#define SDL_FAKE_ON
#ifdef SDL_FAKE_ON
#include "../test/SDL_Fake.h"
#else
#include "SDL2/SDL.h"
#endif

class MainWindow
{
public:
    MainWindow(int screenPosX = SDL_WINDOWPOS_UNDEFINED,
               int screenPosY = SDL_WINDOWPOS_UNDEFINED,
               int screenWidth = SCREEN_WIDTH,
               int screenHeight = SCREEN_HEIGHT);
    MainWindow(const MainWindow &wnd) = delete;
    MainWindow &operator=(const MainWindow &wnd) = delete;
    ~MainWindow();
    void init();
    bool isActive() const;
    void destroy();
    SDL_Window *get() const noexcept;
    void UpdateWindowTitle(int score, int fps);

private:
    static constexpr int SCREEN_WIDTH = 640;
    static constexpr int SCREEN_HEIGHT = 640;

    bool m_isActive{false};
    SDL_Window *m_window{NULL};
    int m_screenPosX;
    int m_screenPosY;
    int m_screenWidth;
    int m_screenHeight;
};
#endif