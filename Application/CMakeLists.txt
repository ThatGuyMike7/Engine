cmake_minimum_required (VERSION 3.16)

set(APPLICATION_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Binary/${CMAKE_SYSTEM_NAME}/${ARCH}/${BUILD_TYPE}")
set(APPLICATION_OUTPUT_NAME "Application")

# Find source files.
file(GLOB_RECURSE APPLICATION_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c"
)

# Create target.
add_executable(${APPLICATION_TARGET} ${APPLICATION_SOURCES})

# Add include directories.
target_include_directories(${APPLICATION_TARGET}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    PRIVATE "${CMAKE_SOURCE_DIR}/Core/Include"
    PRIVATE "${CMAKE_SOURCE_DIR}/Graphics/Include"
)

set_common_options(${APPLICATION_TARGET} ${APPLICATION_OUTPUT_DIR} ${APPLICATION_OUTPUT_NAME})

# Define `ENGINE_APPLICATION_DEBUG` in Debug mode.
if (${BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(${APPLICATION_TARGET} PRIVATE "ENGINE_APPLICATION_DEBUG")
endif ()
