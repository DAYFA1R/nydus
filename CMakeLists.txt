cmake_minimum_required(VERSION 3.15)
project(nydus)

add_executable(nyd src/main.cpp)

find_package(yaml-cpp REQUIRED)
find_package(GTest REQUIRED)

target_link_libraries(nyd
  PRIVATE
    yaml-cpp::yaml-cpp
    gtest::gtest
)

