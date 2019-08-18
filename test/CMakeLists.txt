add_library(sdl_fake OBJECT SDL_Fake.h)
target_link_libraries(sdl_fake
                      gmock_main)

add_executable(test testMainWindow.cpp)

target_link_libraries(test 
                      gtest_main
                      gmock_main
                      )

add_test(NAME test COMMAND test)