cmake_minimum_required(VERSION 3.11)

project(MaiaRenderer LANGUAGES C CXX)

set(MAIA_RENDERER_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory("Source")
add_subdirectory("Test")
