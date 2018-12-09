include (FetchContent)

FetchContent_Declare (
    D3DX12
    URL "https://raw.githubusercontent.com/Microsoft/DirectX-Graphics-Samples/636f9441f1a9d6dfca04bbcc9a1c1f316c01053d/Libraries/D3DX12/d3dx12.h"
)

FetchContent_GetProperties (D3DX12)
if (NOT d3dx12_POPULATED)

    FetchContent_Populate (D3DX12)
    
endif ()

find_path (D3DX12_INCLUDE_DIR "d3dx12.h" PATHS "${d3dx12_SOURCE_DIR}" NO_DEFAULT_PATH)
mark_as_advanced (D3DX12_INCLUDE_DIR)

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (D3DX12
    REQUIRED_VARS 
        D3DX12_INCLUDE_DIR
)

if (D3DX12_FOUND AND NOT TARGET D3D12::D3DX12)
    
    add_library (D3DX12 INTERFACE IMPORTED)

    set_target_properties(D3DX12 PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${D3DX12_INCLUDE_DIR}"
    )

endif()