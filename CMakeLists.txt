cmake_minimum_required(VERSION 3.17)
project(vertexCover)

set(CMAKE_CXX_STANDARD 14)

add_executable(vertexCover main.cpp graph.cpp graph.h vertex_cover_ga.cpp vertex_cover_ga.h)