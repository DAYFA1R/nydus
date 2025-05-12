cmake_minimum_required(VERSION 3.15)
project(nydus)
enable_testing()

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Set compiler settings for C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find and reference the conan deps
find_package(yaml-cpp REQUIRED)
find_package(GTest REQUIRED)

# Debug mode only block
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Build Nydus Core
file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS src/*.cpp)
list(FILTER ALL_SOURCES EXCLUDE REGEX ".*/main.cpp$") # filter out main.cpp from all src files
set(NYD_SOURCES ${ALL_SOURCES})
add_library(nydus_core STATIC ${NYD_SOURCES})
target_link_libraries(nydus_core
PUBLIC
yaml-cpp::yaml-cpp # link yaml-cpp to Nydus Core
)

add_executable(nyd src/main.cpp) # link Nydus Core and main.cpp to form the main executable
target_link_libraries(nyd
PRIVATE
nydus_core
)

# Build tests
file(GLOB_RECURSE NYD_TESTS CONFIGURE_DEPENDS tests/*.cpp)
add_executable(nydus_tests ${NYD_TESTS})
target_link_libraries(nydus_tests # link Nydus Core to GTest
  PRIVATE
    nydus_core
    gtest::gtest
)

# Google Test include and test discovery
include(GoogleTest)
gtest_discover_tests(nydus_tests)
