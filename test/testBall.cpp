#include "../src/MainWindow.cpp"
#include "../src/Renderer.cpp"
#include "../src/BaseBlock.cpp"

class Ball : public BaseBlock
{
public:
    Ball(SDL_Rect brickBlock, Color c) : BaseBlock(brickBlock, c)
    {
    }

private:
};

class GameBrick : public TestFixture
{
public:
    SDL_Rect testBlock{0, 0, 32 * 4, 32 * 2};
    Color color = Colors::Yellow;
    Ball ball{testBlock, color};
};

MATCHER_P(EqBlock, expected, "")
{
    return arg.x == expected.x && arg.y == expected.y && arg.w == expected.w && arg.h == expected.h;
}

TEST_F(GameBrick, BallBlockInitializedAfterCreation)
{
    ASSERT_THAT(ball.getBlock(), EqBlock(testBlock));
}
