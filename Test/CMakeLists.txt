cmake_minimum_required(VERSION 3.25)
project(MatrixTest C)

set(CMAKE_C_STANDARD 11)

add_executable(MatrixTest main.c)
target_link_libraries(MatrixTest libmatrix.a)

