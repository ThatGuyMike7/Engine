cmake_minimum_required(VERSION 3.16)

set(CORE_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Binary/${CMAKE_SYSTEM_NAME}/${ARCH}/${BUILD_TYPE}")
set(CORE_OUTPUT_NAME "Core")

# Find source files.
file(GLOB_RECURSE CORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c"
)

# Without this, CMake won't compile files with ".c" extension.
set_source_files_properties(${CORE_SOURCES} PROPERTIES LANGUAGE CXX)

# Create target.
add_library(${CORE_TARGET} STATIC ${CORE_SOURCES})

# Add include directories.
target_include_directories(${CORE_TARGET}
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source"
    PRIVATE "${SDL2_DIR}/Include"
)

set_common_options(${CORE_TARGET} ${CORE_OUTPUT_DIR} ${CORE_OUTPUT_NAME})

# Define `ENGINE_CORE_DEBUG` in Debug mode.
if (${BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(${CORE_TARGET} PRIVATE "ENGINE_CORE_DEBUG")
endif ()
