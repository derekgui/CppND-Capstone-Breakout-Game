#include "../src/MainWindow.cpp"
#include "../src/Renderer.cpp"
#include "../src/Paddle.cpp"

class GamePaddle : public TestFixture
{
public:
    Paddle paddle{0, 0};
    SDL_Rect testBlock{0, 0, 32 * 6, 32 * 6};
    MainWindow wnd;
    Renderer rnd{wnd};
};

MATCHER_P(EqBlock, expected, "")
{
    return arg.x == expected.x && arg.y == expected.y && arg.w == expected.w && arg.h == expected.h;
}

TEST_F(GamePaddle, PaddleBlockInitializedAfterCreation)
{
    ASSERT_THAT(paddle.getPaddleBlock(), EqBlock(testBlock));
}

TEST_F(GamePaddle, DrawSelfOntoGraphicFrame)
{
    EXPECT_CALL(*_SDL_Mock, SDL_SetRenderDrawColor(_, _, _, _, _)).Times(1);
    EXPECT_CALL(*_SDL_Mock, SDL_RenderFillRect(_, _)).Times(1);

    paddle.drawSelf(rnd);
}