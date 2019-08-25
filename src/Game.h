#ifndef GAME_H
#define GAME_H

#include "MainWindow.h"
#include "Renderer.h"
#include "Controller.h"
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"
#include "FrameTimer.h"

class Game
{
public:
    Game(MainWindow &wnd);
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;
    bool isNotQuited() const;
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
    FrameTimer frameTimer;
    bool isTurnLost{false};
    bool isGameStarted{false};
    bool isGameOver{false};
    bool isPaddleShrinked{false};
    int turnCount{3};
    int score{0};
    int hitCount{0};
    int fps_count{0};

private:
    bool paddleMissedBall() const;
    void replaceBall();
    void repalcePaddle();
    void updateScore();
    void updateBallSpeed();
    void updateHitCount();
};

#endif