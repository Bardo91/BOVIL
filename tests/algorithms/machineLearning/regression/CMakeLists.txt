set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})
# Loading 3rd party libraries.
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(testRegression test.cpp)

target_link_libraries(testRegression PUBLIC BOViL)
add_test(testRegression1 testRegression)