set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})
# Loading 3rd party libraries.
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(testNeuronalNetwork test.cpp)
target_link_libraries(testNeuronalNetwork PUBLIC BOViL)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/wineDataset.txt ${CMAKE_CURRENT_BINARY_DIR}/wineDataset.txt COPYONLY)

add_test(testNeuronalNetwork1 testNeuronalNetwork)