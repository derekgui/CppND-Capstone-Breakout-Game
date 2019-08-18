#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <iostream>
#include "../test/SDL_Fake.h"

class MainWindow
{
public:
    MainWindow(int screenPosX, int screenPosY, int screenWidth, int screenHeight);
    MainWindow(const MainWindow &wnd) = delete;
    MainWindow &operator=(const MainWindow &wnd) = delete;
    ~MainWindow();
    void init();
    bool isActive() const;
    void destroy();

private:
    bool m_isActive{false};
    SDL_Window *m_window{NULL};
    int m_screenPosX;
    int m_screenPosY;
    int m_screenWidth;
    int m_screenHeight;
};

MainWindow::MainWindow(int screenPosX, int screenPosY, int screenWidth, int screenHeight)
    : m_screenPosX(screenPosX),
      m_screenPosY(screenPosY),
      m_screenWidth(screenWidth),
      m_screenHeight(screenHeight)
{
    //   init();
}

MainWindow::~MainWindow()
{
    destroy();
}

void MainWindow::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cerr << "SDL could not initialized! SDL_Error: "
                  << SDL_GetError() << "\n";
    else
    {
        m_window = SDL_CreateWindow("Breakout Game",
                                    m_screenPosX,
                                    m_screenPosY,
                                    m_screenWidth,
                                    m_screenHeight,
                                    SDL_WINDOW_SHOWN);
        if (NULL == m_window)
            std::cerr << "Window could not be created! SDL_Error: "
                      << SDL_GetError() << "\n";
        else
            m_isActive = true;
    }
}

bool MainWindow::isActive() const { return m_isActive; }

void MainWindow::destroy()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

#endif