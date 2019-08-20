#include "../src/MainWindow.h"

class Renderer
{
public:
    Renderer(const MainWindow &wnd)
    {
    }
};

class GameRenderer : public TestFixture
{
public:
    static constexpr int SCREEN_WIDTH = 640;
    static constexpr int SCREEN_HEIGHT = 480;
    std::unique_ptr<SDL_Window> test_window = std::make_unique<SDL_Window>();

public:
    void arrangeWindowCreation(SDL_Window *returnWindowAddress)
    {
        InSequence seq;

        ON_CALL(*_SDL_Mock, SDL_Init(_)).WillByDefault(Return(0));

        ON_CALL(*_SDL_Mock, SDL_CreateWindow(_,
                                             _,
                                             _,
                                             _,
                                             _,
                                             SDL_WINDOW_SHOWN))
            .WillByDefault(Return(returnWindowAddress));
    }
};

TEST_F(GameRenderer, CheckMainWindowIsActive)
{
    arrangeWindowCreation(test_window.get());

    MainWindow wnd{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT};

    ASSERT_THAT(wnd.isActive(), Eq(true));
}
