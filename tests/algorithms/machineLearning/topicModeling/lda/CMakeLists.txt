set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})
# Loading 3rd party libraries.

add_executable(testLda test.cpp)

target_link_libraries(testLda PUBLIC BOViL)
add_test(testLda1 testLda)