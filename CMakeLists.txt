cmake_minimum_required(VERSION 3.24)
project(r-type-client)
project(r-type-server)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

FIND_PACKAGE(raylib REQUIRED)

include_directories(${raylib_INCLUDE_DIR})

include_directories(.)

add_subdirectory(Engine)

add_executable(r-type-client Client/main.cpp Client/RaylibGraphicLib.cpp Client/RaylibGraphicLib.h Client/RaylibWindow.cpp Client/RaylibWindow.h Client/RaylibTexture.cpp Client/RaylibTexture.h Client/FixTextureComponent.cpp Client/FixTextureComponent.h Client/DrawFixTextureSystem.cpp Client/DrawFixTextureSystem.h Client/PingPacketConsumer.cpp Client/PingPacketConsumer.h Client/StayAliveSystem.cpp Client/StayAliveSystem.h)

add_executable(r-type-server Server/main.cpp Server/ClientData.cpp Server/ClientData.h Server/RTypeServer.cpp Server/RTypeServer.h Server/PingPacketConsumer.cpp Server/PingPacketConsumer.h Server/TimeoutSystem.cpp Server/TimeoutSystem.h)

target_link_libraries(r-type-client eng raylib)
target_link_libraries(r-type-server eng)
if(WIN32)
    target_link_libraries(r-type-server wsock32 ws2_32)
    target_link_libraries(r-type-client wsock32 ws2_32)
    target_link_libraries(r-type-server -static)
    target_link_libraries(r-type-client -static)
endif()