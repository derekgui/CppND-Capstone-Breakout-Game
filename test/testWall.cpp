#include "../src/MainWindow.cpp"
#include "../src/Renderer.cpp"
#include "../src/BaseBlock.cpp"
#include "../src/Wall.cpp"

class GameWall : public TestFixture
{
public:
    Wall wall;
};

TEST_F(GameWall, MapIsLoadedAfterCreation)
{
    ASSERT_THAT(wall.isLoaded(), Eq(true));
}

MATCHER_P(EqBlock, expected, "")
{
    return arg.x == expected.x && arg.y == expected.y && arg.w == expected.w && arg.h == expected.h;
}

TEST_F(GameWall, SetColorAndPostionoftheSpecificOne)
{
    SDL_Rect testBlock{0, 0, 32 * 2, 32};
    int brickNumber = 0;

    wall.setBrick(brickNumber)->Block().w = 32 * 2;
    wall.setBrick(brickNumber)->Block().h = 32;

    wall.setBrick(brickNumber)->blockColor() = Colors::Yellow;

    ASSERT_THAT(wall.getBrick(brickNumber)->Block(), EqBlock(testBlock));
    ASSERT_THAT(wall.getBrick(brickNumber)->blockColor(), Eq(Colors::Yellow));
}