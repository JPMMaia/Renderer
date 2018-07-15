# Enable testing and find GoogleTest:
enable_testing()
set(GoogleTest_DIR "${MAIA_UTILITIES_ROOT}/CMake")
find_package(GoogleTest REQUIRED CONFIG)

# Add unit tests:
add_subdirectory(UnitTest)
add_test(MaiaRendererTest MaiaRendererUnitTest)
