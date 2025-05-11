cmake_minimum_required(VERSION 3.15)
project(nydus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE NYD_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(nyd ${NYD_SOURCES})

find_package(yaml-cpp REQUIRED)
find_package(GTest REQUIRED)

target_link_libraries(nyd
  PRIVATE
    yaml-cpp::yaml-cpp
    gtest::gtest
)
