cmake_minimum_required(VERSION 3.10)
project(hello_ceres)

include_directories("/usr/include/eigen3")
find_package(Ceres REQUIRED)
include_directories(
 # include
 ${CERES_INCLUDE_DIRS}
)

# Should be larger than version 14 to avoid ‘integer_sequence’ is not a member of ‘std’ error
set(CMAKE_CXX_STANDARD 17)

# Only Ceres itself should be compiled with CERES_BUILDING_SHARED_LIBRARY
# defined, any users of Ceres will have CERES_USING_SHARED_LIBRARY defined
# for them in Ceres' config.h if appropriate.
if (BUILD_SHARED_LIBS)
  remove_definitions(-DCERES_BUILDING_SHARED_LIBRARY)
endif()

# Build all example file in the example folder
file(GLOB example_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/example example/*.cc)
foreach(example_source ${example_sources})
	string(REPLACE ".cc" "" example_name ${example_source})
        set(example_binary_name ${example_name})

        add_executable(${example_binary_name} example/${example_source})
        target_link_libraries(${example_binary_name} ceres)
endforeach()

add_subdirectory(example/slam)