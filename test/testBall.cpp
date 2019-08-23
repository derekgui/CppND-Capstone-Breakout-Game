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
    Ball ball{testBlock, color};
};

MATCHER_P(EqBlock, expected, "")
{
    return arg.x == expected.x && arg.y == expected.y && arg.w == expected.w && arg.h == expected.h;
}

TEST_F(GameBall, BallBlockInitializedAfterCreation)
{
    ASSERT_THAT(ball.Block(), EqBlock(testBlock));
}

TEST_F(GameBall, IsNotCollideIfItsBottomlessThanAnothersTop)
{
    SDL_Rect paddleBlock{0, 64, 32 * 6, 32};

    Paddle paddle{paddleBlock, Colors::Red};

    ASSERT_THAT(ball.checkCollision(paddle), Eq(false));
}

TEST_F(GameBall, IsNotCollideIfItsTopGreatThanAnothersBottom)
{
    ball.Block().y = 64;

    SDL_Rect paddleBlock{0, 0, 32 * 6, 32};

    Paddle paddle{paddleBlock, Colors::Red};

    ASSERT_THAT(ball.checkCollision(paddle), Eq(false));
}

TEST_F(GameBall, IsNotCollideIfItsRightLessThanAnothersLeft)
{
    SDL_Rect paddleBlock{64, 0, 32 * 6, 32};

    Paddle paddle{paddleBlock, Colors::Red};

    ASSERT_THAT(ball.checkCollision(paddle), Eq(false));
}

TEST_F(GameBall, IsNotCollideIfItsLeftGreatThanAnothersRight)
{
    ball.Block().x = 32 * 6 + 1;

    SDL_Rect paddleBlock{0, 0, 32 * 6, 32};

    Paddle paddle{paddleBlock, Colors::Red};

    ASSERT_THAT(ball.checkCollision(paddle), Eq(false));
}

TEST_F(GameBall, CheckCollidingSituation)
{
    ball.Block().x = 32 * 5;
    ball.Block().y = 20;

    SDL_Rect paddleBlock{0, 0, 32 * 6, 32};

    Paddle paddle{paddleBlock, Colors::Red};

    ASSERT_THAT(ball.checkCollision(paddle), Eq(true));
}

TEST_F(GameBall, DefaultVelocityToZeroAfterCreation)
{
    ASSERT_THAT(ball.velocity().vx, Eq(0));
    ASSERT_THAT(ball.velocity().vy, Eq(0));
}

TEST_F(GameBall, SetVelocityToAValue)
{
    ball.velocity().vx = 2;
    ball.velocity().vy = 3;

    ASSERT_THAT(ball.velocity().vx, Eq(2));
    ASSERT_THAT(ball.velocity().vy, Eq(3));
}

TEST_F(GameBall, UpdateBallPositionWithVelocity)
{
    ball.velocity().vx = 2;
    ball.velocity().vy = 3;

    ball.update();

    ASSERT_THAT(ball.Block().x, Eq(2));
    ASSERT_THAT(ball.Block().y, Eq(3));
}

TEST_F(GameBall, BounceBackIfTheBallHitLeftScreenBoundary)
{
    ball.velocity().vx = 1;
    ball.Block().x = -2;

    ball.update();

    ASSERT_THAT(ball.Block().x, Eq(0));
    ASSERT_THAT(ball.velocity().vx, Eq(-1));
}

TEST_F(GameBall, BounceBackIfTheBallHitRightScreenBoundary)
{
    int rightMost = MainWindow::SCREEN_WIDTH - 1 - ball.Block().w;

    ball.Block().x = MainWindow::SCREEN_WIDTH + 1;
    ball.velocity().vx = 1;

    ball.update();

    ASSERT_THAT(ball.Block().x, Eq(rightMost));
    ASSERT_THAT(ball.velocity().vx, Eq(-1));
}

TEST_F(GameBall, BounceBackIfTheBallHitTheTopScreenBoundary)
{
    ball.velocity().vy = 1;
    ball.Block().y = -2;

    ball.update();

    ASSERT_THAT(ball.Block().y, Eq(0));
    ASSERT_THAT(ball.velocity().vy, Eq(-1));
}

TEST_F(GameBall, BounceBackIfTheBallHitBottomScreenBoundary)
{
    int bottomMost = MainWindow::SCREEN_HEIGHT - 1 - ball.Block().h;

    ball.Block().y = MainWindow::SCREEN_HEIGHT + 1;
    ball.velocity().vy = 1;

    ball.update();

    ASSERT_THAT(ball.Block().y, Eq(bottomMost));
    ASSERT_THAT(ball.velocity().vy, Eq(-1));
}

TEST_F(GameBall, BounceBackIFTheBallHitAnotherBlock)
{
    ball.Block().x = 32 * 5;
    ball.Block().y = 20;
    ball.velocity().vy = 1;

    SDL_Rect paddleBlock{0, 0, 32 * 6, 32};

    Paddle paddle{paddleBlock, Colors::Red};

    ball.checkCollision(paddle);
    ball.update();

    ASSERT_THAT(ball.velocity().vy, Eq(-1));
}