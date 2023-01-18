cmake_minimum_required(VERSION 3.24)
project(r-type-client)
project(r-type-server)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

FIND_PACKAGE(raylib REQUIRED)

include_directories(${raylib_INCLUDE_DIR})

include_directories(.)

add_subdirectory(Engine)

add_executable(r-type-client Client/main.cpp Client/RaylibGraphicLib.cpp Client/RaylibGraphicLib.h Client/RaylibWindow.cpp Client/RaylibWindow.h Client/RaylibTexture.cpp Client/RaylibTexture.h)

add_executable(r-type-server Server/main.cpp)

target_link_libraries(r-type-client eng raylib)
target_link_libraries(r-type-server eng)
