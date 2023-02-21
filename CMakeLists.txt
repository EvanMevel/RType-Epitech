cmake_minimum_required(VERSION 3.16)
project(r-type-server)
project(r-type-client)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

FIND_PACKAGE(raylib REQUIRED)

include_directories(${raylib_INCLUDE_DIR})

include_directories(.)

add_subdirectory(Engine)
add_subdirectory(Server)
add_subdirectory(Client)

target_link_libraries(r-type-client eng raylib)
target_link_libraries(r-type-server eng)
if(WIN32)
    target_link_libraries(r-type-server wsock32 ws2_32)
    target_link_libraries(r-type-client wsock32 ws2_32)
    target_link_libraries(r-type-server -static)
    target_link_libraries(r-type-client -static)
else()
    target_link_libraries(r-type-server -static-libgcc -static-libstdc++ -lpthread)
    target_link_libraries(r-type-client -static-libgcc -static-libstdc++ -lpthread)
endif()