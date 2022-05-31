cmake_minimum_required(VERSION 3.10)

project(assetter)

##c++ 17
set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC_FILES *.cpp)

add_subdirectory(zip)
add_subdirectory(SQLiteCpp)

add_executable(assetter ${SRC_FILES})
target_link_libraries(assetter zip SQLiteCpp)

