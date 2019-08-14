add_executable(test testGTest.cpp)

target_link_libraries(test 
                      gtest_main
                      gmock_main 
                      example)

add_test(NAME test COMMAND test)