cmake_minimum_required(VERSION 3.24)
project(r-type-client)
project(r-type-server)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

FIND_PACKAGE(raylib REQUIRED)

include_directories(${raylib_INCLUDE_DIR})

include_directories(.)

add_subdirectory(Engine)

add_executable(r-type-client Client/main.cpp Client/ray/RaylibGraphicLib.cpp Client/ray/RaylibGraphicLib.h Client/ray/RaylibWindow.cpp Client/ray/RaylibWindow.h Client/ray/RaylibTexture.cpp Client/ray/RaylibTexture.h Client/FixTextureComponent.cpp Client/FixTextureComponent.h Client/DrawFixTextureSystem.cpp Client/DrawFixTextureSystem.h Client/CreateButton.cpp Client/CreateButton.h Client/MainMenu.h Client/MainMenu.cpp Client/Consumers/PingPacketConsumer.cpp Client/Consumers/PingPacketConsumer.h Client/StayAliveSystem.cpp Client/StayAliveSystem.h Client/Consumers/HandshakeResponseConsumer.cpp Client/Consumers/HandshakeResponseConsumer.h Client/Consumers/PlayerInfoConsumer.cpp Client/Consumers/PlayerInfoConsumer.h Client/ClientNetServer.h Client/PlayerKeysSystem.cpp Client/PlayerKeysSystem.h Client/Player.cpp Client/Player.h Client/PlayerMoveSystem.cpp Client/PlayerMoveSystem.h Client/ray/RaylibAnimation.cpp Client/ray/RaylibAnimation.h Client/AnimationComponent.cpp Client/AnimationComponent.h Client/AnimationSystem.cpp Client/AnimationSystem.h)

add_executable(r-type-server Server/main.cpp Server/ClientData.cpp Server/ClientData.h Server/RTypeServer.cpp Server/RTypeServer.h Server/PingPacketConsumer.cpp Server/PingPacketConsumer.h Server/TimeoutSystem.cpp Server/TimeoutSystem.h Server/HandshakeConsumer.cpp Server/HandshakeConsumer.h Server/ServerVelocitySystem.cpp Server/ServerVelocitySystem.h)

target_link_libraries(r-type-client eng raylib)
target_link_libraries(r-type-server eng)
if(WIN32)
    target_link_libraries(r-type-server wsock32 ws2_32)
    target_link_libraries(r-type-client wsock32 ws2_32)
    target_link_libraries(r-type-server -static)
    target_link_libraries(r-type-client -static)
endif()