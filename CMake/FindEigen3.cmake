find_package (Eigen3 3.3 NO_MODULE)

if (NOT TARGET Eigen3::Eigen)

    include (FetchContent)
    FetchContent_Declare (
        Eigen3
        URL "http://bitbucket.org/eigen/eigen/get/3.3.5.zip"
    )

    FetchContent_GetProperties (Eigen3)
    if (NOT eigen3_POPULATED)

        FetchContent_Populate (Eigen3)

        list (APPEND CMAKE_MODULE_PATH "${eigen3_SOURCE_DIR}")
        find_package (Eigen3 3.3 REQUIRED NO_MODULE)

    endif()

endif ()
