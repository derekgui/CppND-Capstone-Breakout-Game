#include "../src/MainWindow.cpp"
#include "../src/Renderer.cpp"
#include "../src/BaseBlock.cpp"

class GamePaddle : public TestFixture
{
public:
    SDL_Rect testBlock{0, 0, 32 * 6, 32};
    BaseBlock baseBlock{testBlock, Colors::Red};
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
    ASSERT_THAT(baseBlock.getBlock(), EqBlock(testBlock));
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

    baseBlock.drawSelf(rnd);
}

TEST_F(GamePaddle, PaddleBlockSizeAdjustable)
{
    SDL_Rect block{2, 2, 32 * 3, 32 * 3};

    baseBlock.setBlock() = block;

    ASSERT_THAT(baseBlock.getBlock(), EqBlock(block));
}