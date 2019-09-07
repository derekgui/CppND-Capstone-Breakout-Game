#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#define SDL_FAKE_ON
#ifdef SDL_FAKE_ON
#include "../test/SDL_Fake.h"
#else
#include "SDL2/SDL.h"
#endif
#include <memory>

struct sdl_deleter
{
    void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
    void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
    void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
};

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
    std::unique_ptr<SDL_Window, sdl_deleter>
    create_window(char const *title, int x, int y, int w, int h, Uint32 flags);

public:
    static constexpr int SCREEN_WIDTH = 640;
    static constexpr int SCREEN_HEIGHT = 640;

private:
    bool m_isActive{false};
    std::unique_ptr<SDL_Window, sdl_deleter> m_window;
    int m_screenPosX;
    int m_screenPosY;
    int m_screenWidth;
    int m_screenHeight;
};
#endif