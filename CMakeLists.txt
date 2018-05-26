cmake_minimum_required(VERSION 3.11)
project(MaiaRenderer)

# Add library to the project and define alias:
add_library(MaiaRenderer)
add_library(Maia::Renderer ALIAS MaiaRenderer)

# Add sources:
target_sources(MaiaRenderer PRIVATE

	# Utilities:
	"Source/D3D12/Utilities/DXUtilities.h"
	"Source/D3D12/Utilities/DXUtilities.cpp"

)

# Link libraries: 
target_link_libraries(MaiaRenderer 

	PUBLIC

	# DXGI:
	DXGI

	# D3D12:
	D3D12

)

# Set compile features:
target_compile_features(MaiaRenderer PRIVATE cxx_std_17)

# Set target linker language:
set_target_properties(MaiaRenderer PROPERTIES LINKER_LANGUAGE CXX)

# Add tests:
add_subdirectory(Test)