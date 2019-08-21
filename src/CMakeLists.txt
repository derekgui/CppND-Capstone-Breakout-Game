cmake_minimum_required(VERSION 3.7)

set(project_BIN ${PROJECT_NAME})

file(GLOB project_SRCS *.cpp *.h)


if(${TESTING} STREQUAL "notest")
    add_executable(${project_BIN} ${project_SRCS})
    target_link_libraries(${project_BIN} 
                            PRIVATE ${SDL2_LIBRARIES}
                            PUBLIC pthread)
endif()