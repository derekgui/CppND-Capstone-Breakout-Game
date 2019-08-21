#ifndef FIXTURE_H
#define FIXTURE_H
#include "ModuleMocks.h"
#include <memory>

namespace ProjectMocks
{
class TestFixture : public ::testing::Test
{
public:
    TestFixture() { _SDL_Mock.reset(new NiceMock<SDL_Mock>()); }
    ~TestFixture()
    {
        _SDL_Mock.reset();
    }

    static std::unique_ptr<SDL_Mock> _SDL_Mock;
};
} // namespace ProjectMocks

#endif
