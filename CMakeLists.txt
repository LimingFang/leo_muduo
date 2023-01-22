cmake_minimum_required(VERSION 3.23)
project(leo_muduo CXX)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

include_directories(src/base src/net)
#add_subdirectory(src/base)
add_subdirectory(src/net)