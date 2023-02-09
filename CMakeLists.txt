cmake_minimum_required(VERSION 3.24)
project(r-type-client)
project(r-type-server)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

FIND_PACKAGE(raylib REQUIRED)

include_directories(${raylib_INCLUDE_DIR})

include_directories(.)

add_subdirectory(Engine)

add_executable(r-type-client Client/main.cpp Client/ray/RaylibGraphicLib.cpp Client/ray/RaylibGraphicLib.h Client/ray/RaylibWindow.cpp Client/ray/RaylibWindow.h Client/ray/RaylibTexture.cpp Client/ray/RaylibTexture.h Client/Textures/FixTextureComponent.cpp Client/Textures/FixTextureComponent.h Client/Textures/DrawFixTextureSystem.cpp Client/Textures/DrawFixTextureSystem.h Client/Textures/CreateButton.cpp Client/Textures/CreateButton.h Client/MainMenu.h Client/MainMenu.cpp Client/Consumers/PingPacketConsumer.cpp Client/Consumers/PingPacketConsumer.h Client/StayAliveSystem.cpp Client/StayAliveSystem.h Client/Consumers/HandshakeResponseConsumer.cpp Client/Consumers/HandshakeResponseConsumer.h Client/Consumers/PlayerInfoConsumer.cpp Client/Consumers/PlayerInfoConsumer.h Client/ClientNetServer.h Client/Player/PlayerKeysSystem.cpp Client/Player/PlayerKeysSystem.h Client/Player/Player.cpp Client/Player/Player.h Client/Player/PlayerMoveSystem.cpp Client/Player/PlayerMoveSystem.h Client/Consumers/EntityInfoConsumer.cpp Client/Consumers/EntityInfoConsumer.h Client/Player/PlayerShootSystem.cpp Client/Player/PlayerShootSystem.h Client/Consumers/EntityDestroyConsumer.cpp Client/Consumers/EntityDestroyConsumer.h Client/Consumers/EntityVelocityPacketConsumer.cpp Client/Consumers/EntityVelocityPacketConsumer.h Client/ray/RaylibAnimation.cpp Client/ray/RaylibAnimation.h Client/AnimationComponent.cpp Client/AnimationComponent.h Client/AnimationSystem.cpp Client/AnimationSystem.h Client/ray/RaylibMouse.cpp Client/ray/RaylibMouse.h Client/MouseSystem.cpp Client/MouseSystem.h Client/ButtonComponent.cpp Client/ButtonComponent.h Client/Scenes.h Client/GameScene.cpp Client/GameScene.h Client/Textures/ScrollingTextureComponent.cpp Client/Textures/ScrollingTextureComponent.h Client/Textures/ScrollingTextureSystem.cpp Client/Textures/ScrollingTextureSystem.h Client/Textures/CreateScrollingTexture.cpp Client/Textures/CreateScrollingTexture.h Client/Sprites/SpriteComponent.cpp Client/Sprites/SpriteComponent.h Client/Sprites/DrawSpriteSystem.cpp Client/Sprites/DrawSpriteSystem.h Client/ray/RaylibMusic.cpp Client/ray/RaylibMusic.h Client/ray/RaylibSound.cpp Client/ray/RaylibSound.h Client/Consumers/ProjectileHitConsumer.cpp Client/Consumers/ProjectileHitConsumer.h Client/Textures/Textures.cpp Client/Textures/Textures.h Client/Sprites/Sprites.h Client/Sounds.h Client/Sprites/Sprites.cpp Client/Sounds.cpp Client/Scenes.cpp)

add_executable(r-type-server Server/main.cpp Server/ClientData.cpp Server/ClientData.h Server/RTypeServer.cpp Server/RTypeServer.h Server/Consumers/PingPacketConsumer.cpp Server/Consumers/PingPacketConsumer.h Server/TimeoutSystem.cpp Server/TimeoutSystem.h Server/Consumers/HandshakeConsumer.cpp Server/Consumers/HandshakeConsumer.h Server/ServerVelocitySystem.cpp Server/ServerVelocitySystem.h Server/Consumers/PlayerMoveConsumer.cpp Server/Consumers/PlayerShootConsumer.cpp Server/ProjectileCleanupSystem.cpp Server/ProjectileCleanupSystem.h Server/EnemyRandomSpawnSystem.cpp Server/EnemyRandomSpawnSystem.h Server/CooldownComponent.cpp Server/CooldownComponent.h Server/EnemyShootSystem.cpp Server/EnemyShootSystem.h Server/ServerColliderSystem.cpp Server/PacketSendingScene.cpp Server/PacketSendingScene.h Server/EnemyInfoComponent.cpp Server/EnemyInfoComponent.h Server/Levels.cpp)

target_link_libraries(r-type-client eng raylib)
target_link_libraries(r-type-server eng)
if(WIN32)
    target_link_libraries(r-type-server wsock32 ws2_32)
    target_link_libraries(r-type-client wsock32 ws2_32)
    target_link_libraries(r-type-server -static)
    target_link_libraries(r-type-client -static)
endif()