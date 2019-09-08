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
    try
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
            throw std::runtime_error(SDL_GetError());
        m_window = create_window("Breakout Game",
                                 m_screenPosX,
                                 m_screenPosY,
                                 m_screenWidth,
                                 m_screenHeight,
                                 SDL_WINDOW_SHOWN);
        if (nullptr == m_window)
            throw windowCreationException(SDL_GetError());
        m_isActive = true;
    }
    catch (const windowCreationException &e)
    {
        std::cerr << "Window could not be created! SDL_Error: "
                  << e.what() << "\n";
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "SDL could not initialized! SDL_Error: "
                  << e.what() << "\n";
    }
}

bool MainWindow::isActive() const { return m_isActive; }

void MainWindow::destroy()
{
    SDL_Quit();
    m_isActive = false;
}

SDL_Window *MainWindow::get() const noexcept
{
    return m_window.get();
}

void MainWindow::UpdateWindowTitle(int score, int fps)
{
    std::string title{"Score: " + std::to_string(score) + " Round: " + std::to_string(fps)};
    SDL_SetWindowTitle(m_window.get(), title.c_str());
}

std::unique_ptr<SDL_Window, sdl_deleter> MainWindow::create_window(char const *title, int x, int y, int w, int h, Uint32 flags)
{
    return std::unique_ptr<SDL_Window, sdl_deleter>(
        SDL_CreateWindow(title, x, y, w, h, flags),
        sdl_deleter());
}