cmake_minimum_required(VERSION 3.16)
project(r-type-server)
project(r-type-client)
project(pong)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

FIND_PACKAGE(raylib REQUIRED)

include_directories(${raylib_INCLUDE_DIR})

include_directories(.)

add_subdirectory(Engine)
add_subdirectory(Ray)
add_subdirectory(Server)
add_subdirectory(Client)
add_subdirectory(Pong)