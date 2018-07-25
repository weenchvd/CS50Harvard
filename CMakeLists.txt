cmake_minimum_required(VERSION 3.10)
project(CS50Harvard C)

set(CMAKE_C_STANDARD 11)

add_executable(CS50Harvard main.c)

add_library(CS50Harvard_L STATIC "C:/_Code/C/CLionProjects/CS50Harvard/Libs/libcs50-8.1.0/cs50.c")

target_link_libraries(CS50Harvard CS50Harvard_L)
