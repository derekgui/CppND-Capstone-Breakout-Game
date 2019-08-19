#include "SDL_Fake.h"

class Controller
{
public:
    bool isAvailable() const { return m_isAvailable; }
    void handleEvent(bool enableCtrl)
    {
        if (enableCtrl)
        {
            m_isAvailable = true;
        }
    }

private:
    bool m_isAvailable{false};
};

class GameController : public testing::Test
{
public:
    Controller controller;
    SDL_Event e;
};

TEST_F(GameController, IsNotAvailableByDefault)
{

    ASSERT_THAT(controller.isAvailable(), Eq(false));
}

TEST_F(GameController, IsAvailableAfterEnable)
{
    bool enableCtrl = true;

    controller.handleEvent(enableCtrl);

    ASSERT_THAT(controller.isAvailable(), Eq(true));
}
