add_library(sdl_fake OBJECT SDL_Fake.cpp)
target_link_libraries(sdl_fake
                      gmock_main)


if(${TESTING} STREQUAL "MainWindow")
    add_executable(test testMainWindow.cpp) 
elseif(${TESTING} STREQUAL "Controller")
    add_executable(test testController.cpp)
elseif(${TESTING} STREQUAL "Renderer")
    add_executable(test testRenderer.cpp)
elseif(${TESTING} STREQUAL "Paddle")
    add_executable(test testPaddle.cpp)
elseif(${TESTING} STREQUAL "BaseBlock")
    add_executable(test testBaseBlock.cpp)
elseif(${TESTING} STREQUAL "Ball")
    add_executable(test testBall.cpp)
elseif(${TESTING} STREQUAL "Wall")
    add_executable(test testWall.cpp)
endif()

target_link_libraries(test sdl_fake)

add_test(NAME test COMMAND test)

unset(TESTING CACHE)