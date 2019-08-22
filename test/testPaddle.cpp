#include "../src/Controller.cpp"
#include "../src/MainWindow.cpp"
#include "../src/Renderer.cpp"
#include "../src/Paddle.cpp"

class GamePaddle : public TestFixture
{
public:
    Paddle paddle{0, 0};
    SDL_Rect testBlock{0, 0, 32 * 6, 32 * 6};
    Controller ctlr;
    MainWindow wnd;
    Renderer rnd{wnd};
    SDL_Event e;
};

MATCHER_P(EqBlock, expected, "")
{
    return arg.x == expected.x && arg.y == expected.y && arg.w == expected.w && arg.h == expected.h;
}

TEST_F(GamePaddle, PaddleBlockInitializedAfterCreation)
{
    ASSERT_THAT(paddle.getBlock(), EqBlock(testBlock));
}

TEST_F(GamePaddle, DrawSelfOntoGraphicFrame)
{
    Color c = Colors::Red;

    EXPECT_CALL(*_SDL_Mock, SDL_SetRenderDrawColor(rnd.get(),
                                                   c.GetR(),
                                                   c.GetG(),
                                                   c.GetB(),
                                                   c.GetA()))
        .Times(1);
    EXPECT_CALL(*_SDL_Mock, SDL_RenderFillRect(rnd.get(), _)).Times(1);

    paddle.drawSelf(rnd);
}

TEST_F(GamePaddle, PaddleBlockSizeAdjustable)
{
    SDL_Rect block{2, 2, 32 * 3, 32 * 3};

    paddle.setBlock(block);

    ASSERT_THAT(paddle.getBlock(), EqBlock(block));
}

TEST_F(GamePaddle, ClampToLeftScreenWhenPositionXLessThanZero)
{
    paddle.setBlock({-1, 0, 32 * 6, 32 * 6});

    paddle.ClampToScreen();

    ASSERT_THAT(paddle.getBlock(), EqBlock(testBlock));
}

TEST_F(GamePaddle, ClampToRightScreenWhenPositionXGreaterThanWidth)
{
    SDL_Rect rightAlignBlock{MainWindow::SCREEN_WIDTH - 1 - 32 * 6, 0, 32 * 6, 32 * 6};

    paddle.setBlock({MainWindow::SCREEN_WIDTH + 1, 0, 32 * 6, 32 * 6});

    paddle.ClampToScreen();

    ASSERT_THAT(paddle.getBlock(), EqBlock(rightAlignBlock));
}

TEST_F(GamePaddle, UpdatePositionToLeftWhenLeftKeyDown)
{
    e.type = SDL_KEYDOWN;
    e.key.keysym.sym = SDLK_LEFT;

    EXPECT_CALL(*_SDL_Mock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(e), Return(1)))
        .WillOnce(Return(0));

    ctlr.handleEvent();

    paddle.setBlock({MainWindow::SCREEN_WIDTH / 2, MainWindow::SCREEN_HEIGHT / 2, 6 * 32, 6 * 32});

    paddle.update(ctlr);

    ASSERT_THAT(paddle.getBlock().x, Eq(MainWindow::SCREEN_WIDTH / 2 - 1));
}

TEST_F(GamePaddle, UpdatePositionToRightWhenRightKeyDown)
{
    e.type = SDL_KEYDOWN;
    e.key.keysym.sym = SDLK_RIGHT;

    EXPECT_CALL(*_SDL_Mock, SDL_PollEvent(_))
        .WillOnce(DoAll(SetArgPointee<0>(e), Return(1)))
        .WillOnce(Return(0));

    ctlr.handleEvent();

    paddle.setBlock({MainWindow::SCREEN_WIDTH / 2, MainWindow::SCREEN_HEIGHT / 2, 6 * 32, 6 * 32});

    paddle.update(ctlr);

    ASSERT_THAT(paddle.getBlock().x, Eq(MainWindow::SCREEN_WIDTH / 2 + 1));
}