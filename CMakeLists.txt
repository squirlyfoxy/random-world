cmake_minimum_required(VERSION 3.10)

project(ogl)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Assimp
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_DISABLE_TESTING 1)

#Include lib/cute_headers, lib/glm
include_directories(
    lib/cute_headers
    lib/cpmath
    lib/perlin-noise
    lib/zip/src
)

link_directories(
    ${CMAKE_BINARY_DIR}/../bin/lib
)

add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)
add_subdirectory(lib/assimp)
add_subdirectory(lib/zip)
add_subdirectory(lib/SQLiteCpp)
add_subdirectory(lib/mimalloc)

file(GLOB My_Source_Files 
    src/*/*.cpp
    src/*/*/*.cpp
    src/*/*/*/*.cpp
    src/*.cpp
)

add_executable(ogl ${My_Source_Files})
target_link_libraries(ogl glfw glad assimp zip SQLiteCpp mimalloc)