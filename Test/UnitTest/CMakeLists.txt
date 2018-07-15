project(MaiaRendererUnitTest VERSION 0.1.0 LANGUAGES C CXX)

add_executable(MaiaRendererUnitTest)
add_executable(Maia::Renderer::UnitTest ALIAS MaiaRendererUnitTest)
gtest_discover_tests(MaiaRendererUnitTest)

target_compile_features(MaiaRendererUnitTest PRIVATE cxx_std_17)

target_include_directories(MaiaRendererUnitTest 
	
	PRIVATE 
		
		"${GOOGLE_TEST_INCLUDE_DIRECTORY}"

)

target_sources(MaiaRendererUnitTest 
	PRIVATE

		"main.cpp"

		"D3D12/Utilities/D3D12_utilities_test.cpp"

)

target_link_libraries(MaiaRendererUnitTest
	debug ${GTEST_DEBUG_LIBRARY} optimized ${GTEST_RELEASE_LIBRARY}
	debug ${GTEST_MAIN_DEBUG_LIBRARY} optimized ${GTEST_MAIN_RELEASE_LIBRARY}
	debug ${GMOCK_DEBUG_LIBRARY} optimized ${GMOCK_RELEASE_LIBRARY}
	debug ${GMOCK_MAIN_DEBUG_LIBRARY} optimized ${GMOCK_MAIN_RELEASE_LIBRARY}
)

target_link_libraries(MaiaRendererUnitTest Maia::Renderer)
