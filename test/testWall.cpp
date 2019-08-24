#include "../src/MainWindow.cpp"
#include "../src/Renderer.cpp"
#include "../src/BaseBlock.cpp"
#include "../src/Wall.cpp"

class GameWall : public TestFixture
{
public:
    Wall wall;
};

MATCHER_P(EqBlock, expected, "")
{
    return arg.x == expected.x && arg.y == expected.y && arg.w == expected.w && arg.h == expected.h;
}

TEST_F(GameWall, MapIsLoadedAfterCreation)
{
    ASSERT_THAT(wall.isLoaded(), Eq(true));
}

TEST_F(GameWall, ReturnTheCorrespodingBrickWhenGet)
{
    int brickNumber;

}