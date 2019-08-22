#include "../src/MainWindow.cpp"
#include "../src/Renderer.cpp"
#include "../src/BaseBlock.cpp"

class ABaseBlock : public TestFixture
{
public:
    SDL_Rect testBlock{0, 0, 32 * 6, 32};
    BaseBlock baseBlock{testBlock, Colors::Red, true};
    MainWindow wnd;
    Renderer rnd{wnd};
    SDL_Event e;
};

MATCHER_P(EqBlock, expected, "")
{
    return arg.x == expected.x && arg.y == expected.y && arg.w == expected.w && arg.h == expected.h;
}

TEST_F(ABaseBlock, InitializedAfterCreation)
{
    ASSERT_THAT(baseBlock.getBlock(), EqBlock(testBlock));
}

TEST_F(ABaseBlock, DrawSelfOntoGraphicFrame)
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

TEST_F(ABaseBlock, ReturnMovabilityAfterCreation)
{
    ASSERT_THAT(baseBlock.isFixed(), Eq(true));
}

TEST_F(ABaseBlock, PaddleBlockSizeAdjustable)
{
    SDL_Rect block{2, 2, 32 * 3, 32 * 3};

    baseBlock.setBlock() = block;

    ASSERT_THAT(baseBlock.getBlock(), EqBlock(block));
}
