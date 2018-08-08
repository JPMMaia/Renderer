project (MaiaRendererUnitTest)

add_executable (MaiaRendererUnitTest)
add_executable (Maia::Renderer::UnitTest ALIAS MaiaRendererUnitTest)

target_compile_features (MaiaRendererUnitTest PRIVATE cxx_std_17)

target_link_libraries (MaiaRendererUnitTest PRIVATE Maia::Renderer)

find_package (GTest REQUIRED)
target_link_libraries (MaiaRendererUnitTest PRIVATE GTest::GTest GTest::Main)

find_package (GMock REQUIRED)
target_link_libraries (MaiaRendererUnitTest PRIVATE GMock::GMock GMock::Main)

target_sources (MaiaRendererUnitTest 
	PRIVATE
		"main.cpp"
		"D3D12/Utilities/D3D12_utilities_test.cpp"
)

gtest_discover_tests (MaiaRendererUnitTest)
