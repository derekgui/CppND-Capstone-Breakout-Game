#include "../src/MainWindow.h"
#include <iostream>

class Renderer
{
public:
    Renderer(const MainWindow &wnd)
        : m_isActive(false),
          m_renderer(nullptr)
    {
        init(wnd);
    }

    ~Renderer()
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
        m_isActive = false;
    }
    void init(const MainWindow &wnd)
    {
        m_renderer = SDL_CreateRenderer(wnd.get(), -1, SDL_RENDERER_ACCELERATED);
        if (nullptr == m_renderer)
            std::cerr << "Rendderer could not be created! SDL Error: "
                      << SDL_GetError() << "\n";
        else
        {
            m_isActive = true;
        }
    }

    bool isActive() const
    {
        return m_isActive;
    }

private:
    bool m_isActive;
    SDL_Renderer *m_renderer;
};

class GameRenderer : public TestFixture
{
public:
    static constexpr int SCREEN_WIDTH = 640;
    static constexpr int SCREEN_HEIGHT = 480;
    std::unique_ptr<SDL_Window> test_window = std::make_unique<SDL_Window>();
    std::unique_ptr<SDL_Renderer> test_renderer = std::make_unique<SDL_Renderer>();
    MainWindow wnd{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT};
    Renderer renderer{wnd};

public:
    void arrangeWindowCreation(SDL_Window *returnWindowAddress)
    {
        InSequence seq;

        ON_CALL(*_SDL_Mock, SDL_Init(_)).WillByDefault(Return(0));

        ON_CALL(*_SDL_Mock, SDL_CreateWindow(_,
                                             _,
                                             _,
                                             _,
                                             _,
                                             SDL_WINDOW_SHOWN))
            .WillByDefault(Return(returnWindowAddress));
    }
};

TEST_F(GameRenderer, CheckMainWindowIsActive)
{
    arrangeWindowCreation(test_window.get());

    wnd.init();

    ASSERT_THAT(wnd.isActive(), Eq(true));
}

TEST_F(GameRenderer, CreateARendererOnInit)
{
    EXPECT_CALL(*_SDL_Mock, SDL_CreateRenderer(_, _, _)).Times(1);
    renderer.init(wnd);
}

TEST_F(GameRenderer, GetErrorWhenCreateRendererFailed)
{
    EXPECT_CALL(*_SDL_Mock, SDL_CreateRenderer(_, -1, _)).WillOnce(Return(static_cast<SDL_Renderer *>(nullptr)));
    EXPECT_CALL(*_SDL_Mock, SDL_GetError()).Times(1);

    renderer.init(wnd);
}

TEST_F(GameRenderer, IsNotActiveByDefault)
{
    ASSERT_THAT(renderer.isActive(), Eq(false));
}

TEST_F(GameRenderer, IsActiveAfterSuccessCreateRenderer)
{
    EXPECT_CALL(*_SDL_Mock, SDL_CreateRenderer(_, -1, _)).WillOnce(Return(test_renderer.get()));

    renderer.init(wnd);

    ASSERT_THAT(renderer.isActive(), Eq(true));
}

TEST_F(GameRenderer, DestroyWindowAndQuitInSequence)
{

    InSequence seq;

    EXPECT_CALL(*_SDL_Mock, SDL_DestroyRenderer(_)).Times(1);
    EXPECT_CALL(*_SDL_Mock, SDL_DestroyWindow(_)).Times(1);
    EXPECT_CALL(*_SDL_Mock, SDL_Quit()).Times(1);
}