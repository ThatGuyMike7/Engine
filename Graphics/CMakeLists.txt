cmake_minimum_required (VERSION 3.16)

set(GRAPHICS_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Binary/${CMAKE_SYSTEM_NAME}/${ARCH}/${BUILD_TYPE}")
set(GRAPHICS_OUTPUT_NAME "Graphics")

# Find source files.
file(GLOB_RECURSE GRAPHICS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c"
)

# Create target.
add_library(${GRAPHICS_TARGET} STATIC ${GRAPHICS_SOURCES})

# Add include directories.
target_include_directories(${GRAPHICS_TARGET}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    PRIVATE "${CMAKE_SOURCE_DIR}/Core/Include"
)

set_common_options(${GRAPHICS_TARGET} ${GRAPHICS_OUTPUT_DIR} ${GRAPHICS_OUTPUT_NAME})

# Define `ENGINE_GRAPHICS_DEBUG` in Debug mode.
if (${BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(${GRAPHICS_TARGET} PRIVATE "ENGINE_GRAPHICS_DEBUG")
endif ()
