cmake_minimum_required (VERSION 2.6)
project(BOViL)
enable_testing()

# Library Projects
add_subdirectory(src)

# Test
add_subdirectory(tests) # Unit tests