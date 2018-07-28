find_path (D3D12RaytracingFallback_INCLUDE_DIR "DirectX-Graphics-Samples/Libraries/D3D12RaytracingFallback/Include/D3D12RaytracingFallback.h")
mark_as_advanced (D3D12RaytracingFallback_INCLUDE_DIR)

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (D3D12RaytracingFallback
    REQUIRED_VARS D3D12RaytracingFallback_INCLUDE_DIR
)

if (D3D12RaytracingFallback_FOUND AND NOT TARGET D3D12::RaytracingFallback)
    add_library (D3D12::RaytracingFallback UNKNOWN IMPORTED)
    set_target_properties (D3D12::RaytracingFallback PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${D3D12RaytracingFallback_INCLUDE_DIR}"
    )
endif ()
