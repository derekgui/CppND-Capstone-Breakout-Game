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