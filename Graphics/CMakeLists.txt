cmake_minimum_required(VERSION 3.16)

set(GRAPHICS_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Binary/${CMAKE_SYSTEM_NAME}/${ARCH}/${BUILD_TYPE}")
set(GRAPHICS_OUTPUT_NAME "Graphics")

# Find source files.
file(GLOB_RECURSE GRAPHICS_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c"
)

# Without this, CMake won't compile files with ".c" extension.
set_source_files_properties(${GRAPHICS_SOURCES} PROPERTIES LANGUAGE CXX)

# Create target.
add_library(${GRAPHICS_TARGET} STATIC ${GRAPHICS_SOURCES})

# Add include directories.
target_include_directories(${GRAPHICS_TARGET}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source"
)

set_common_options(${GRAPHICS_TARGET} ${GRAPHICS_OUTPUT_DIR} ${GRAPHICS_OUTPUT_NAME})
