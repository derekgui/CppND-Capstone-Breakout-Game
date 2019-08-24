#ifndef GAME_H
#define GAME_H

#include "MainWindow.h"
#include "Renderer.h"
#include "Controller.h"
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"

class Game
{
public:
    Game(MainWindow &wnd);
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    void Run();

private:
    void ComposeFrame();
    void Update();

private:
    static constexpr std::size_t kFramesPerSecond{60};
    static constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};

    MainWindow &wnd;
    Renderer rnd;
    Controller controller;
    Ball ball;
    Paddle paddle;
    Wall wall;
};

#endif