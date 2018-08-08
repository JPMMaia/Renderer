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
)

target_sources (MaiaRenderer 
	PRIVATE
		"Maia/Renderer/D3D12/Utilities/D3D12_utilities.h"
		"Maia/Renderer/D3D12/Utilities/D3D12_utilities.cpp"
)

include (FetchContent)
FetchContent_Declare (
	MaiaUtilities
	GIT_REPOSITORY "https://github.com/JPMMaia/Utilities.git"
	GIT_TAG "master"
)

FetchContent_GetProperties (MaiaUtilities)
if (NOT maiautilities_POPULATED)
	FetchContent_Populate (MaiaUtilities)
    add_subdirectory (${maiautilities_SOURCE_DIR} ${maiautilities_BINARY_DIR})
endif ()


install (TARGETS MaiaRenderer EXPORT MaiaRendererTargets
	LIBRARY DESTINATION "lib"
	ARCHIVE DESTINATION "lib"
	RUNTIME DESTINATION "bin"
	INCLUDES DESTINATION "include"
)
install (DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/Maia"
		DESTINATION "include"
        FILES_MATCHING PATTERN "*.hpp" ".h"
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
