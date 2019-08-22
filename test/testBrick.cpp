#include "../src/MainWindow.cpp"
#include "../src/Renderer.cpp"
#include "../src/BaseBlock.cpp"

class Brick : public BaseBlock
{
public:
    Brick(SDL_Rect brickBlock, Color c) : BaseBlock(brickBlock, c)
    {
    }
};

class GameBrick : public TestFixture
{
public:
    SDL_Rect testBlock{0, 0, 32 * 4, 32 * 2};
    Color color = Colors::Yellow;
    Brick brick{testBlock, color};
};

MATCHER_P(EqBlock, expected, "")
{
    return arg.x == expected.x && arg.y == expected.y && arg.w == expected.w && arg.h == expected.h;
}

TEST_F(GameBrick, BrickBlockInitializedAfterCreation)
{
    ASSERT_THAT(brick.getBlock(), EqBlock(testBlock));
}