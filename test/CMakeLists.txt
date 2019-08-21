add_library(sdl_fake OBJECT SDL_Fake.h SDL_Fake.cpp)
target_link_libraries(sdl_fake
                      gmock_main)


if(${TESTING} STREQUAL "MainWindow")
    add_executable(test testMainWindow.cpp) 
elseif(${TESTING} STREQUAL "Controller")
    add_executable(test testController.cpp)
elseif(${TESTING} STREQUAL "Renderer")
    add_executable(test testRenderer.cpp)
else()

endif()

target_link_libraries(test gmock_main)

add_test(NAME test COMMAND test)

unset(TESTING CACHE)