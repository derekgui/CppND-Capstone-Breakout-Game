add_library(sdl_fake OBJECT SDL_Fake.h)
target_link_libraries(sdl_fake
                      gmock_main)


if(${TESTING} STREQUAL "MainWindow")
    add_executable(test testMainWindow.cpp)
    target_link_libraries(test gmock_main) 
elseif(${TESTING} STREQUAL "Controller")
    add_executable(test testController.cpp)
    target_link_libraries(test gmock_main) 
else()

endif()

add_test(NAME test COMMAND test)

unset(TESTING CACHE)