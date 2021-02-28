cmake_minimum_required(VERSION 3.17)
project(lab C)

set(CMAKE_C_STANDARD 99)

add_executable(lab Matrix.c Matrix.h main.c)