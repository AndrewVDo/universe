cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Universe)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Universe src/main.cpp src/universe.cpp src/CelestialBody.cpp)
target_link_libraries(Universe sfml-graphics sfml-audio)