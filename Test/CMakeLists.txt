enable_testing ()
find_package (GTest REQUIRED)
find_package (GMock REQUIRED)

add_subdirectory (UnitTest)
add_test (MaiaRendererTest MaiaRendererUnitTest)
