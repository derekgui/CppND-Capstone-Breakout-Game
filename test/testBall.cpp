#include "../src/MainWindow.cpp"
#include "../src/Renderer.cpp"
#include "../src/BaseBlock.cpp"

class Ball : public BaseBlock
{
public:
    Ball(SDL_Rect brickBlock, Color c, bool isFixed)
        : BaseBlock(brickBlock, c, isFixed)
    {
    }

private:
};

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
