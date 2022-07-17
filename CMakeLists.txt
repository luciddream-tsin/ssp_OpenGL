cmake_minimum_required(VERSION 3.22)
project(SSPOpenGL)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins)

link_directories(${CMAKE_SOURCE_DIR}/bins)

include_directories(glfw/include)
add_subdirectory(glfw)
include_directories(glad/include)
add_subdirectory(glad)


add_subdirectory(01_window)
add_subdirectory(03_triangle)
add_subdirectory(04_shader)