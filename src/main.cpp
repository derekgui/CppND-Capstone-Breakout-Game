#include "Game.h"
#include <iostream>

int main()
{
    MainWindow wnd;

    Game theGame(wnd);

    while (theGame.isNotQuited())
    {
        theGame.Run();
    }

    return 0;
}
