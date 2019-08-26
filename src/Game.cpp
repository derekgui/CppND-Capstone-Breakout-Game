#include "Game.h"
#include <future>

Game::Game(MainWindow &wnd)
    : wnd(wnd),
      rnd(wnd),
      ball({MainWindow::SCREEN_WIDTH / 2, MainWindow::SCREEN_HEIGHT * 3 / 5,
            BaseBlock::baseBlockWidth,
            BaseBlock::baseBlockHeight},
           Colors::Red),
      paddle({(MainWindow::SCREEN_WIDTH / 2 - 3 * BaseBlock::baseBlockWidth),
              (MainWindow::SCREEN_HEIGHT * 5 / 6),
              BaseBlock::baseBlockWidth * 6, BaseBlock::baseBlockHeight},
             Colors::Red)
{
}

void Game::Run()
{
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;

    frame_start = SDL_GetTicks();
    rnd.clearScreen();
    Update();
    ComposeFrame();
    rnd.updateScreen();
    wnd.UpdateWindowTitle(score, turnCount);
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_duration = frame_end - frame_start;

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < kMsPerFrame)
    {
        SDL_Delay(kFramesPerSecond - frame_duration);
    }
}

void Game::Update()
{
    std::future<void> ftr = std::async(std::launch::deferred, &Controller::handleEvent, std::ref(controller));

    if (isGameStarted && !isGameOver && !isTurnLost)
    {

        paddle.update(controller);

        paddle.ClampToScreen();

        wall.update(ball);

        ball.update();

        if (ball.checkCollision(paddle))
        {
            ball.update();
        }

        if (paddleMissedBall())
        {
            replaceBall();

            repalcePaddle();

            isTurnLost = true;
            turnCount--;

            if (turnCount == 0)
            {
                isGameOver = true;
            }
        }
        //if ball hit the screen top then shrink the paddle.
        if (ball.Block().y == 0 && !isPaddleShrinked)
        {
            paddle.shrink();
            isPaddleShrinked = true;
        }
        updateScore();

        updateBallSpeed();
    }
    //start Game With SPACE BAR key.
    else
    {
        if (controller.keyStatus() == KEYSTATUS::SPACE_DOWN)
        {
            isGameStarted = true;
            isTurnLost = false;
        }
    }

    ftr.get();
}

void Game::ComposeFrame()
{
    ball.drawSelf(rnd);
    wall.drawSelf(rnd);
    paddle.drawSelf(rnd);
}

//Game is Not Quited when controller not processed close window key.
bool Game::isNotQuited() const
{
    return controller.isAvailable();
}

bool Game::paddleMissedBall() const
{
    return ball.Block().y + ball.Block().h > paddle.Block().y + paddle.Block().h;
}

void Game::replaceBall()
{

    ball.Block().x = MainWindow::SCREEN_WIDTH / 2;
    ball.Block().y = MainWindow::SCREEN_HEIGHT * 3 / 5;
}

void Game::repalcePaddle()
{
    paddle.Block().x = MainWindow::SCREEN_WIDTH / 2 - 3 * BaseBlock::baseBlockWidth;
    paddle.Block().y = MainWindow::SCREEN_HEIGHT * 5 / 6;
}

void Game::updateScore()
{
    score = wall.getBrokenBricks().yellow * 1 + wall.getBrokenBricks().green * 3 + wall.getBrokenBricks().orange * 5 + wall.getBrokenBricks().red * 7;
}

void Game::updateHitCount()
{
    hitCount = wall.getBrokenBricks().yellow + wall.getBrokenBricks().green + wall.getBrokenBricks().orange + wall.getBrokenBricks().red;
}

void Game::updateBallSpeed()
{
    int lastHitCount = hitCount;

    updateHitCount();
    if (lastHitCount != 4 && hitCount == 4)
    {
        ball.velocity().vx += 1;
        ball.velocity().vy += 1;
    }
    else if (lastHitCount != 8 && hitCount == 8)
    {
        ball.velocity().vx += 2;
        ball.velocity().vy += 2;
    }
    else if (lastHitCount != 12 && hitCount == 12)
    {
        ball.velocity().vx += 4;
        ball.velocity().vy += 4;
    }
}