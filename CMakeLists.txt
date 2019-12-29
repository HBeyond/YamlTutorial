cmake_minimum_required(VERSION 2.8)

project(YamlTurorial)

find_package(Eigen3 REQUIRED)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#link_directories(~/thz_libs/yaml-cpp-master/build)

#include_directories(~/thz_libs/yaml-cpp-master/include/yaml-cpp)

add_executable(${PROJECT_NAME} main.cpp Parameters.hpp)
target_link_libraries(${PROJECT_NAME} yaml-cpp)
target_link_libraries (${PROJECT_NAME} Eigen3::Eigen)
