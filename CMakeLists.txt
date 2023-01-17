cmake_minimum_required(VERSION 3.24)
project(r-type-client)
project(r-type-server)

set(CMAKE_CXX_STANDARD 17)
include_directories(.)
add_subdirectory(Engine)

add_executable(r-type-client Client/main.cpp)

add_executable(r-type-server Server/main.cpp)

target_link_libraries(r-type-client eng)
target_link_libraries(r-type-server eng)
