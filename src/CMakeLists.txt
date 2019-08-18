cmake_minimum_required(VERSION 3.7)

set(project_BIN ${PROJECT_NAME})

file(GLOB project_SRCS *.cpp *.h)

add_executable(${project_BIN} ${project_SRCS})

target_link_libraries(${project_BIN} 
                      PRIVATE ${SDL2_LIBRARIES}
                      sdl_fake
                      PUBLIC pthread)

add_library(MainWindow OBJECT MainWindow.h MainWindow.cpp)
target_link_libraries(MainWindow)