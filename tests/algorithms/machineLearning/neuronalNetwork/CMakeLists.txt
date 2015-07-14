set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})
# Loading 3rd party libraries.
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(testNeuronalNetwork test.cpp)

target_link_libraries(testNeuronalNetwork PUBLIC BOViL)
add_test(testNeuronalNetwork1 testNeuronalNetwork)