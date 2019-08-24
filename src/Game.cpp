#include "Game.h"

Game::Game(MainWindow &wnd)
    : wnd(wnd),
      rnd(wnd),
      ball({MainWindow::SCREEN_WIDTH / 2, MainWindow::SCREEN_HEIGHT * 3 / 5, BaseBlock::baseBlockWidth, BaseBlock::baseBlockHeight}, Colors::Red),
      paddle({(MainWindow::SCREEN_WIDTH / 2 - 3 * BaseBlock::baseBlockWidth),
              (MainWindow::SCREEN_HEIGHT * 5 / 6),
              6 * BaseBlock::baseBlockWidth, BaseBlock::baseBlockHeight},
             Colors::Red)
{
}

void Game::Run()
{
    while (controller.isAvailable())
    {
        rnd.clearScreen();
        Update();
        ComposeFrame();
        rnd.updateScreen();
    }
}

void Game::Update()
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.handleEvent();
    ball.update();
    paddle.update(controller);
    paddle.ClampToScreen();
    wall.update(ball);

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

void Game::ComposeFrame()
{

    wall.drawSelf(rnd);
    ball.drawSelf(rnd);
    paddle.drawSelf(rnd);
}