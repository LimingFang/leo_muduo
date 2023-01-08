cmake_minimum_required(VERSION 3.14)
project(leo_muduo CXX)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CXX_FLAGS
 -g
 -Wall
 -Wextra
 -Werror
 -Wconversion
 -Wno-unused-parameter
 -Wno-sign-conversion
 -Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -march=native
 -std=c++20
 -fsanitize=address
 )
 
add_subdirectory(muduo/base)
add_subdirectory(muduo/net)