cmake_minimum_required(VERSION 3.19)
project(graph_lab)

find_package(GLUT REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(graph_lab main.cpp Line.h Point.h Circle.h Oval.h)

target_link_libraries(graph_lab opengl32)
target_link_libraries(graph_lab glu32)
target_link_libraries(graph_lab User32)
target_link_libraries(graph_lab freeglut)



