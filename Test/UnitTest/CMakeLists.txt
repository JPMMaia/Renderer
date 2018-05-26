project(MaiaRendererUnitTest VERSION 0.1.0 LANGUAGES C CXX)

# Add test executable:
add_executable(MaiaRendererUnitTest)
add_executable(Maia::Renderer::UnitTest ALIAS MaiaRendererUnitTest)
gtest_discover_tests(MaiaRendererUnitTest)

# Set compile features:
target_compile_features(MaiaRendererUnitTest PRIVATE cxx_std_17)

# Add includes directories:
target_include_directories(MaiaRendererUnitTest PRIVATE 

	# Renderer:
	"${CMAKE_SOURCE_DIR}/Source"

	# Google Test:
	"${GOOGLE_TEST_INCLUDE_DIRECTORY}"

)

# Add test sources:
target_sources(MaiaRendererUnitTest PRIVATE

	# Main:
	"Source/main.cpp"

	# D3D12
	"Source/D3D12/Utilities/DXUtilitiesTest.cpp"

)

# Link Google Test and Google Mock libraries:
target_link_libraries(MaiaRendererUnitTest
	debug ${GTEST_DEBUG_LIBRARY} optimized ${GTEST_RELEASE_LIBRARY}
	debug ${GTEST_MAIN_DEBUG_LIBRARY} optimized ${GTEST_MAIN_RELEASE_LIBRARY}
	debug ${GMOCK_DEBUG_LIBRARY} optimized ${GMOCK_RELEASE_LIBRARY}
	debug ${GMOCK_MAIN_DEBUG_LIBRARY} optimized ${GMOCK_MAIN_RELEASE_LIBRARY}
)

# Link libraries:
target_link_libraries(MaiaRendererUnitTest Maia::Renderer)
