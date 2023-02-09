cmake_minimum_required(VERSION 3.24)
project(r-type-client)
project(r-type-server)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

FIND_PACKAGE(raylib REQUIRED)

include_directories(${raylib_INCLUDE_DIR})

include_directories(.)

add_subdirectory(Engine)

add_executable(r-type-client Client/main.cpp Client/ray/RaylibGraphicLib.cpp Client/ray/RaylibGraphicLib.h Client/ray/RaylibWindow.cpp Client/ray/RaylibWindow.h Client/ray/RaylibTexture.cpp Client/ray/RaylibTexture.h Client/FixTextureComponent.cpp Client/FixTextureComponent.h Client/DrawFixTextureSystem.cpp Client/DrawFixTextureSystem.h Client/CreateButton.cpp Client/CreateButton.h Client/MainMenu.h Client/MainMenu.cpp Client/Consumers/PingPacketConsumer.cpp Client/Consumers/PingPacketConsumer.h Client/StayAliveSystem.cpp Client/StayAliveSystem.h Client/Consumers/HandshakeResponseConsumer.cpp Client/Consumers/HandshakeResponseConsumer.h Client/Consumers/PlayerInfoConsumer.cpp Client/Consumers/PlayerInfoConsumer.h Client/ClientNetServer.h Client/PlayerKeysSystem.cpp Client/PlayerKeysSystem.h Client/Player.cpp Client/Player.h Client/PlayerMoveSystem.cpp Client/PlayerMoveSystem.h Client/Consumers/EntityInfoConsumer.cpp Client/Consumers/EntityInfoConsumer.h Client/PlayerShootSystem.cpp Client/PlayerShootSystem.h Client/Consumers/EntityDestroyConsumer.cpp Client/Consumers/EntityDestroyConsumer.h Client/Consumers/EntityVelocityPacketConsumer.cpp Client/Consumers/EntityVelocityPacketConsumer.h Client/ray/RaylibAnimation.cpp Client/ray/RaylibAnimation.h Client/AnimationComponent.cpp Client/AnimationComponent.h Client/AnimationSystem.cpp Client/AnimationSystem.h Client/ray/RaylibMouse.cpp Client/ray/RaylibMouse.h Client/MouseSystem.cpp Client/MouseSystem.h Client/HitboxFixComponent.cpp Client/HitboxFixComponent.h Client/SceneEnum.h Client/GameScene.cpp Client/GameScene.h Client/ScrollingTextureComponent.cpp Client/ScrollingTextureComponent.h Client/ScrollingTextureSystem.cpp Client/ScrollingTextureSystem.h Client/CreateScrollingTexture.cpp Client/CreateScrollingTexture.h Client/SpriteComponent.cpp Client/SpriteComponent.h Client/DrawSpriteSystem.cpp Client/DrawSpriteSystem.h Client/ray/RaylibMusic.cpp Client/ray/RaylibMusic.h Client/ray/RaylibSound.cpp Client/ray/RaylibSound.h Client/SoundManager.cpp Client/SoundManager.h Client/Consumers/ProjectileHitConsumer.cpp Client/Consumers/ProjectileHitConsumer.h Client/Textures.cpp Client/Textures.h Client/Sprites.h)

add_executable(r-type-server Server/main.cpp Server/ClientData.cpp Server/ClientData.h Server/RTypeServer.cpp Server/RTypeServer.h Server/Consumers/PingPacketConsumer.cpp Server/Consumers/PingPacketConsumer.h Server/TimeoutSystem.cpp Server/TimeoutSystem.h Server/Consumers/HandshakeConsumer.cpp Server/Consumers/HandshakeConsumer.h Server/ServerVelocitySystem.cpp Server/ServerVelocitySystem.h Server/Consumers/PlayerMoveConsumer.cpp Server/Consumers/PlayerShootConsumer.cpp Server/ProjectileCleanupSystem.cpp Server/ProjectileCleanupSystem.h Server/EnemyRandomSpawnSystem.cpp Server/EnemyRandomSpawnSystem.h Server/CooldownComponent.cpp Server/CooldownComponent.h Server/EnemyShootSystem.cpp Server/EnemyShootSystem.h Server/ServerColliderSystem.cpp Server/PacketSendingScene.cpp Server/PacketSendingScene.h Server/EnemyInfoComponent.cpp Server/EnemyInfoComponent.h Server/Levels.cpp)

target_link_libraries(r-type-client eng raylib)
target_link_libraries(r-type-server eng)
if(WIN32)
    target_link_libraries(r-type-server wsock32 ws2_32)
    target_link_libraries(r-type-client wsock32 ws2_32)
    target_link_libraries(r-type-server -static)
    target_link_libraries(r-type-client -static)
endif()