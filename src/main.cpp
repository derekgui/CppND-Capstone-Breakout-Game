#include "Game.h"
#include <iostream>

int main()
{
    MainWindow wnd{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MainWindow::SCREEN_WIDTH, MainWindow::SCREEN_HEIGHT};

    Game theGame(wnd);

    theGame.Run();

    return 0;
}
