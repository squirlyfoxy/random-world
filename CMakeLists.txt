cmake_minimum_required(VERSION 3.10)

project(ogl)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

#Include lib/cute_headers, lib/glm
include_directories(
    lib/cute_headers
    lib/cpmath
    lib/perlin-noise
)

link_directories(
    ${CMAKE_BINARY_DIR}/../bin/lib
)

add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)
add_subdirectory(lib/assimp)

file(GLOB My_Source_Files 
    src/*/*.cpp
    src/*/*/*.cpp
    src/*/*/*/*.cpp
    src/*.cpp
)

add_executable(ogl ${My_Source_Files})
target_link_libraries(ogl glfw glad assimp)
    