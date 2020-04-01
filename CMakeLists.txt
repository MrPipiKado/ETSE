cmake_minimum_required(VERSION 3.15)
project(ETSE C)

set(CMAKE_C_STANDARD 99)

add_executable(ETSE main.c functions.c)

target_link_libraries(ETSE cs50)