project (MaiaRendererUnitTest)

add_executable (MaiaRendererUnitTest)
add_executable (Maia::Renderer::UnitTest ALIAS MaiaRendererUnitTest)

target_link_libraries (MaiaRendererUnitTest
	PRIVATE
		GTest::GTest 
		GTest::Main
		GMock::GMock
		GMock::Main
		Maia::Renderer
)

target_sources (MaiaRendererUnitTest 
	PRIVATE
		"main.cpp"
		"D3D12/Utilities/D3D12_utilities_test.cpp"
)

target_compile_features (MaiaRendererUnitTest PRIVATE cxx_std_17)

gtest_discover_tests (MaiaRendererUnitTest)
