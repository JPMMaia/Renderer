include (FetchContent)

FetchContent_Declare (
    Eigen3
    URL "http://bitbucket.org/eigen/eigen/get/3.3.5.zip"
)

FetchContent_GetProperties (Eigen3)
if (NOT eigen3_POPULATED)
    FetchContent_Populate (Eigen3)
endif ()

find_path (Eigen3_INCLUDE_DIR "Eigen/Eigen" PATHS "${eigen3_SOURCE_DIR}" NO_DEFAULT_PATH)
mark_as_advanced (Eigen3_INCLUDE_DIR)

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (Eigen3
    REQUIRED_VARS 
        Eigen3_INCLUDE_DIR
)

if (Eigen3_FOUND AND NOT TARGET Eigen3::Eigen)
    
    add_subdirectory("${eigen3_SOURCE_DIR}" "${eigen3_BINARY_DIR}" EXCLUDE_FROM_ALL)
    
endif ()
