cmake_minimum_required (VERSION 3.11)

project (MaiaRenderer)

list (APPEND CMAKE_MODULE_PATH "${MAIA_RENDERER_ROOT}/CMake")
list (APPEND CMAKE_MODULE_PATH "${MAIA_UTILITIES_ROOT}/CMake")

add_subdirectory ("Source")
add_subdirectory ("Test")
