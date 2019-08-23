#include "../src/MainWindow.cpp"
#include "../src/Controller.cpp"
#include "../src/Renderer.cpp"
#include "../src/Paddle.cpp"
#include "../src/BaseBlock.cpp"
#include "../src/Ball.cpp"

class GameBall : public TestFixture
{
public:
    SDL_Rect testBlock{0, 0, 32, 32};
    Color color = Colors::Red;
    Ball ball{testBlock, color, false};
};

MATCHER_P(EqBlock, expected, "")
{
    return arg.x == expected.x && arg.y == expected.y && arg.w == expected.w && arg.h == expected.h;
}

TEST_F(GameBall, BallBlockInitializedAfterCreation)
{
    ASSERT_THAT(ball.getBlock(), EqBlock(testBlock));
}

TEST_F(GameBall, IsNotCollideIfItsBottomlessThanAnothersTop)
{
    SDL_Rect paddleBlock{0, 64, 32 * 6, 32};

    Paddle paddle{paddleBlock, Colors::Red, false};

    ASSERT_THAT(ball.checkCollision(paddle), Eq(false));
}

TEST_F(GameBall, IsNotCollideIfItsTopGreatThanAnothersBottom)
{
    ball.setBlock().y = 64;

    SDL_Rect paddleBlock{0, 0, 32 * 6, 32};

    Paddle paddle{paddleBlock, Colors::Red, false};

    ASSERT_THAT(ball.checkCollision(paddle), Eq(false));
}

TEST_F(GameBall, IsNotCollideIfItsRightLessThanAnothersLeft)
{
    SDL_Rect paddleBlock{64, 0, 32 * 6, 32};

    Paddle paddle{paddleBlock, Colors::Red, false};

    ASSERT_THAT(ball.checkCollision(paddle), Eq(false));
}

TEST_F(GameBall, IsNotCollideIfItsLeftGreatThanAnothersRight)
{
    ball.setBlock().x = 32 * 6 + 1;

    SDL_Rect paddleBlock{0, 0, 32 * 6, 32};

    Paddle paddle{paddleBlock, Colors::Red, false};

    ASSERT_THAT(ball.checkCollision(paddle), Eq(false));
}