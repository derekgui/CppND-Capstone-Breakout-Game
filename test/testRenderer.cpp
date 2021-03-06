#include "../src/MainWindow.cpp"
#include "../src/Renderer.cpp"

class GameRenderer : public TestFixture
{
public:
    static constexpr int SCREEN_WIDTH = 640;
    static constexpr int SCREEN_HEIGHT = 640;
    std::unique_ptr<SDL_Window> test_window = std::make_unique<SDL_Window>();
    std::unique_ptr<SDL_Renderer> test_renderer = std::make_unique<SDL_Renderer>();
    MainWindow wnd{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT};
    Renderer renderer{wnd};

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

    wnd.init();

    ASSERT_THAT(wnd.isActive(), Eq(true));
}

TEST_F(GameRenderer, CreateARendererOnInit)
{
    EXPECT_CALL(*_SDL_Mock, SDL_CreateRenderer(_, _, _)).Times(1);
    renderer.init(wnd);
}

TEST_F(GameRenderer, GetErrorWhenCreateRendererFailed)
{
    EXPECT_CALL(*_SDL_Mock, SDL_CreateRenderer(_, -1, _)).WillOnce(Return(static_cast<SDL_Renderer *>(nullptr)));
    EXPECT_CALL(*_SDL_Mock, SDL_GetError()).Times(1);

    renderer.init(wnd);
}

TEST_F(GameRenderer, IsNotActiveByDefault)
{
    ASSERT_THAT(renderer.isActive(), Eq(false));
}

TEST_F(GameRenderer, IsActiveAfterSuccessCreateRenderer)
{
    EXPECT_CALL(*_SDL_Mock, SDL_CreateRenderer(_, -1, _)).WillOnce(Return(test_renderer.get()));

    renderer.init(wnd);

    ASSERT_THAT(renderer.isActive(), Eq(true));
}

TEST_F(GameRenderer, DestroyWindowAndQuitInSequence)
{

    InSequence seq;

    EXPECT_CALL(*_SDL_Mock, SDL_DestroyRenderer(_)).Times(1);
    EXPECT_CALL(*_SDL_Mock, SDL_DestroyWindow(_)).Times(1);
    EXPECT_CALL(*_SDL_Mock, SDL_Quit()).Times(1);
}

TEST_F(GameRenderer, ClearScreen)
{
    EXPECT_CALL(*_SDL_Mock, SDL_SetRenderDrawColor(_, _, _, _, _)).Times(1);
    EXPECT_CALL(*_SDL_Mock, SDL_RenderClear(_)).Times(1);

    renderer.clearScreen();
}

TEST_F(GameRenderer, UpdateScreen)
{
    EXPECT_CALL(*_SDL_Mock, SDL_RenderPresent(_)).Times(1);

    renderer.updateScreen();
}

TEST_F(GameRenderer, DrawRect)
{
    EXPECT_CALL(*_SDL_Mock, SDL_SetRenderDrawColor(_, 0xD3, 0xD3, 0xD3, 0xFF)).Times(1);
    EXPECT_CALL(*_SDL_Mock, SDL_RenderFillRect(_, _)).Times(1);

    SDL_Rect block;
    Color c = Colors::LightGray;

    renderer.drawRect(&block, c);
}

TEST_F(GameRenderer, ReturnRendererRawPointWhenGet)
{
    ON_CALL(*_SDL_Mock, SDL_CreateRenderer(_, -1, _)).WillByDefault(Return(test_renderer.get()));

    renderer.init(wnd);

    ASSERT_THAT(renderer.get(), Eq(test_renderer.get()));
}