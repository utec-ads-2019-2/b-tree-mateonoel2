cmake_minimum_required(VERSION 3.15)
project(b_tree_mateonoel2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(b_tree_mateonoel2
        btree.h
        main.cpp
        node.h)
