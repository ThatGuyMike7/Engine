# CMake Notes:
#
# `CMAKE_CURRENT_SOURCE_DIR` refers to the directory of the current CMakeLists.txt being processed,
# `CMAKE_SOURCE_DIR` to the directory of the top-most CMakeLists.txt.
#
# `GLOB_RECURSE` collects all files recursively in all subdirectories,
# `GLOB` all files in the directory.
#
# `CMAKE_BUILD_TYPE` can be "Debug", "Release", "RelWithDebInfo", "MinSizeRel", ...
#
# `CMAKE_SYSTEM_NAME` can be "Windows", "Linux", "Darwin", ...

cmake_minimum_required(VERSION 3.16)
project(Engine CXX)

function(set_common_options TARGET TARGET_OUTPUT_DIR TARGET_OUTPUT_NAME)
    if (MSVC)
        target_compile_options(${TARGET} PRIVATE
            /WX                 # Treat warnings as errors.
            /W4                 # Warning level.
            /wd4458             # Suppress warning "declaration of 'x' hides class member".
            /wd4996             # Suppress warning "'fopen': This function or variable may be unsafe. Consider using fopen_s instead."
            /wd4146             # Suppress warning "unary minus operator applied to unsigned type, result still unsigned".
            /wd4100             # Suppress warning "unreferenced formal parameter".
            /wd4324             # Suppress warning "structure was padded due to alignment specifier".
            #/fsanitize=address
        )
    else ()
        target_compile_options(${TARGET} PRIVATE
            -pedantic           # No extensions.
            -Wall -Wextra       # Warnings.
            -Werror             # Warnings are errors.
            #-fsanitize=address
        )
    endif ()

    # With Visual Studio, use multiple processes to build faster.
    if (CMAKE_GENERATOR MATCHES "Visual Studio")
        target_compile_options(${TARGET} PRIVATE /MP)
    endif ()

    # Specify output directory, output name and C++ standard.
    set_target_properties(${TARGET} PROPERTIES
        # "$<0:>" is a generator expression, it prevents multi-configuration generators
        # from appending a per-configuration subdirectory to the specified path.
        RUNTIME_OUTPUT_DIRECTORY "${TARGET_OUTPUT_DIR}/$<0:>" # For executable targets.
        ARCHIVE_OUTPUT_DIRECTORY "${TARGET_OUTPUT_DIR}/$<0:>" # For static library targets.
        OUTPUT_NAME "${TARGET_OUTPUT_NAME}"
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
    )

    # Define "ENGINE_DEBUG" in Debug mode.
    if (${BUILD_TYPE} STREQUAL "Debug")
        target_compile_definitions(${TARGET} PRIVATE "ENGINE_DEBUG")
    endif ()

    # Define system name, for example "ENGINE_WINDOWS"
    # Check python build script for more information as it sets `SYSTEM_NAME`.
    target_compile_definitions(${TARGET} PRIVATE "ENGINE_${SYSTEM_NAME}")
endfunction()

set(ARCH "Undefined" CACHE STRING "Name of target architecture, must match architecture of host machine. For example \"x64\" or \"ARM64\".")
if ((NOT DEFINED ARCH) OR (${ARCH} STREQUAL "Undefined"))
    message(FATAL_ERROR "`ARCH` is undefined.")
endif ()

set(SYSTEM_NAME "Undefined" CACHE STRING "Name of target system name.")
if ((NOT DEFINED SYSTEM_NAME) OR (${SYSTEM_NAME} STREQUAL "Undefined"))
    message(FATAL_ERROR "`SYSTEM_NAME` is undefined.")
endif ()

set(BUILD_TYPE "Undefined" CACHE STRING "Build type. Must be one of [\"Debug\", \"Release\", \"RelWithDebInfo\", \"MinSizeRel\"]")
if ((NOT DEFINED BUILD_TYPE) OR (${BUILD_TYPE} STREQUAL "Undefined") OR
                                (NOT ${BUILD_TYPE} STREQUAL "Debug") AND
                                (NOT ${BUILD_TYPE} STREQUAL "Release") AND
                                (NOT ${BUILD_TYPE} STREQUAL "RelWithDebInfo") AND
                                (NOT ${BUILD_TYPE} STREQUAL "MinSizeRel"))
    message(FATAL_ERROR "`BUILD_TYPE` is undefined.")
endif ()

set(SDL2_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/SDL2")
find_library(SDL2_TARGET
    NAMES "SDL2"
    PATHS "${SDL2_DIR}/Binary/${CMAKE_SYSTEM_NAME}/${ARCH}"
    PATH_SUFFIXES "lib64" "lib" "so" "a"
    NO_DEFAULT_PATH
)

set(CORE_TARGET "Core")
set(GRAPHICS_TARGET "Graphics")
set(APPLICATION_TARGET "Application")

add_subdirectory(${CORE_TARGET})
add_subdirectory(${GRAPHICS_TARGET})
add_subdirectory(${APPLICATION_TARGET})

target_link_libraries(${CORE_TARGET} PRIVATE ${SDL2_TARGET})
target_link_libraries(${GRAPHICS_TARGET} PUBLIC ${CORE_TARGET})
target_link_libraries(${APPLICATION_TARGET} PRIVATE ${CORE_TARGET} PRIVATE ${GRAPHICS_TARGET})