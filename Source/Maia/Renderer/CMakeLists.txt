project (MaiaRenderer)

add_library (MaiaRenderer)
add_library (Maia::Renderer ALIAS MaiaRenderer)

target_compile_features (MaiaRenderer PRIVATE cxx_std_17)
set_target_properties (MaiaRenderer PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories (MaiaRenderer 
	PUBLIC
		"${CMAKE_CURRENT_SOURCE_DIR}/../.."
)

target_sources (MaiaRenderer 
	PRIVATE

		"D3D12/Utilities/D3D12_utilities.h"
		"D3D12/Utilities/D3D12_utilities.cpp"

)

target_link_libraries (MaiaRenderer 
	PUBLIC
		DXGI
		D3D12
		WindowsApp
)
