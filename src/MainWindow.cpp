#include "MainWindow.h"
#include <iostream>
#include <string>

MainWindow::MainWindow(int screenPosX, int screenPosY, int screenWidth, int screenHeight)
    : m_screenPosX(screenPosX),
      m_screenPosY(screenPosY),
      m_screenWidth(screenWidth),
      m_screenHeight(screenHeight)
{
    init();
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
    m_window = NULL;
    SDL_Quit();
    m_isActive = false;
}

SDL_Window *MainWindow::get() const noexcept
{
    return m_window;
}

void MainWindow::UpdateWindowTitle(int score, int fps)
{
    std::string title{"Score: " + std::to_string(score) + " Round: " + std::to_string(fps)};
    SDL_SetWindowTitle(m_window, title.c_str());
}