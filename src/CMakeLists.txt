cmake_minimum_required (VERSION 2.6)
if(POLICY CMP0048)
cmake_policy(SET CMP0048 OLD)
endif()
project(BOViL)

# Collect all sources
file(GLOB_RECURSE BOVIL_SOURCE_FILES "bovil/*.cpp" "bovil/*.h" "bovil/*.inl")

# Clasify sources according to folder structure.
# This creates a nice layout for the project in visual studio
# This macro is courtesy of http://www.cmake.org/pipermail/cmake/2013-November/056336.html
macro(GroupSources curdir)
	file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
		${PROJECT_SOURCE_DIR}/${curdir}/*)
	foreach(child ${children})
		if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			GroupSources(${curdir}/${child})
		else()
			string(REPLACE "/" "\\" groupname ${curdir})
			source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
		endif()
	endforeach()
endmacro()

GroupSources(bovil)

# Compiler specific options
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()


set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH} /usr/local/lib /usr/lib)
# Loading 3rd party libraries.
find_package(Eigen3)

if(NOT DEFINED ${EIGEN3_INCLUDE_DIR})	
	if(WIN32)
		set(EIGEN3_INCLUDE_DIR "C:/Program Files (x86)/Eigen/include/eigen3")
	elseif(UNIX)
		set(EIGEN3_INCLUDE_DIR "/usr/local/include/eigen3")
	endif()
	
	file(GLOB_RECURSE EIGEN_INCLUDE_FILES "${EIGEN3_INCLUDE_DIR}/*")

	if("${EIGEN_INCLUDE_FILES}" STREQUAL  "")
		message( FATAL_ERROR "Can't find Eigen3 library" )
	endif()
endif()

# Library
add_library(BOViL STATIC ${BOVIL_SOURCE_FILES})
target_include_directories(BOViL PUBLIC ${PROJECT_SOURCE_DIR}/bovil)
target_include_directories(BOViL PUBLIC ${EIGEN3_INCLUDE_DIR})
