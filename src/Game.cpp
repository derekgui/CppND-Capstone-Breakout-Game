#include "Game.h"

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
    rnd.clearScreen();
    Update();
    ComposeFrame();
    rnd.updateScreen();
}

void Game::Update()
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    frame_start = SDL_GetTicks();

    controller.handleEvent();
    // Input, Update, Render - the main game loop.
    if (isGameStarted && !isGameOver && !isTurnLost)
    {
        paddle.update(controller);
        paddle.ClampToScreen();

        if (ball.checkCollision(paddle))
        {
            ball.update();
        }

        wall.update(ball);
        ball.update();

        if ((ball.Block().y + ball.Block().h) > paddle.Block().y + paddle.Block().h)
        {
            //rest ball palce
            ball.Block().x = MainWindow::SCREEN_WIDTH / 2;
            ball.Block().y = MainWindow::SCREEN_HEIGHT * 3 / 5;

            //reset paddle place
            paddle.Block().x = MainWindow::SCREEN_WIDTH / 2 - 3 * BaseBlock::baseBlockWidth;
            paddle.Block().y = MainWindow::SCREEN_HEIGHT * 5 / 6;

            isTurnLost = true;
            turnCount--;
            if (turnCount == 0)
            {
                isGameOver = true;
            }
        }

        if (ball.Block().y < MainWindow::SCREEN_HEIGHT / 2)
        {
            paddle.shrink();
        }

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000)
        {
            wnd.UpdateWindowTitle(2, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < kMsPerFrame)
        {
            SDL_Delay(kFramesPerSecond - frame_duration);
        }
    }
    else
    {
        if (controller.keyStatus() == KEYSTATUS::SPACE_DOWN)
        {
            isGameStarted = true;
            isTurnLost = false;
        }
    }
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