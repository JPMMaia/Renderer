project (MaiaRenderer VERSION 0.0.1)

add_library (MaiaRenderer)
add_library (Maia::Renderer ALIAS MaiaRenderer)

set_target_properties (MaiaRenderer PROPERTIES 
	LINKER_LANGUAGE "CXX"
)

target_compile_features (MaiaRenderer 
	PRIVATE 
		cxx_std_17
)

target_include_directories (MaiaRenderer 
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
		$<INSTALL_INTERFACE:include/Maia/Renderer>
)

target_link_libraries (MaiaRenderer 
	PRIVATE
		DXGI
		D3D12
		WindowsApp
)
 
 target_link_libraries (MaiaRenderer PRIVATE Maia::Utilities)

find_package (D3D12RaytracingFallback REQUIRED)
target_link_libraries (MaiaRenderer PUBLIC D3D12::RaytracingFallback)
add_custom_command (TARGET MaiaRenderer POST_BUILD COMMAND ${CMAKE_COMMAND} -E 
    copy_directory
        "$<TARGET_PROPERTY:D3D12::RaytracingFallback,RUNTIME_DIRECTORY>" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries (MaiaRenderer PUBLIC Eigen3::Eigen)

target_sources (MaiaRenderer 
	PRIVATE
		"Maia/Renderer/D3D12/D3D12_renderer.hpp"
		"Maia/Renderer/D3D12/D3D12_renderer.cpp"
		"Maia/Renderer/D3D12/Utilities/D3D12_utilities.hpp"
		"Maia/Renderer/D3D12/Utilities/D3D12_utilities.cpp"
)


install (TARGETS MaiaRenderer EXPORT MaiaRendererTargets
	LIBRARY DESTINATION "lib"
	ARCHIVE DESTINATION "lib"
	RUNTIME DESTINATION "bin"
	INCLUDES DESTINATION "include"
)
install (DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/Maia"
		DESTINATION "include"
        FILES_MATCHING PATTERN "*.hpp"
)
install (EXPORT MaiaRendererTargets
	FILE "MaiaRendererTargets.cmake"
	NAMESPACE Maia::
	DESTINATION "lib/cmake/Maia/Renderer"
)

include (CMakePackageConfigHelpers)
write_basic_package_version_file ("${CMAKE_CURRENT_BINARY_DIR}/MaiaRendererConfigVersion.cmake"
	VERSION ${MaiaRenderer_VERSION}
	COMPATIBILITY SameMajorVersion
)
install (FILES "MaiaRendererConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/MaiaRendererConfigVersion.cmake"
	DESTINATION "lib/cmake/Maia/Renderer"
)
