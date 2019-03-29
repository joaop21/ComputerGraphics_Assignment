cmake_minimum_required(VERSION 3.6)

# Project Name
PROJECT(Generator)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(${PROJECT_NAME} generator.cpp box.cpp plane.cpp cone.cpp sphere.cpp writeFile.cpp asteroids.cpp torus.cpp)

add_definitions(-std=c++11 -Wall )
