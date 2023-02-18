cmake_minimum_required(VERSION 3.16)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

option(LUA_ENABLE_TESTING "Build and run tests" OFF)
add_subdirectory(lua)

include_directories(.)
include_directories(Component)

add_library(eng
        Component/HealthComponent.cpp
        Component/HitboxComponent.cpp
        Component/TeamComponent.cpp

        Engine.cpp
        Engine.h
        Entity.cpp
        Entity.h
        IConsumer.h
        Network/Packets/IPacket.h
        ISystem.h
        Scene.cpp
        Scene.h Graphic/IGraphicLib.cpp Graphic/IGraphicLib.h Graphic/IWindow.h Graphic/ITexture.h Graphic/ColorCodes.h EntityType.h ISystem.cpp EntityManager.cpp EntityManager.h Network/CrossPlatformSocket.cpp Network/CrossPlatformSocket.h Network/NetworkListener.cpp Network/NetworkListener.h Network/Packets/PacketSerializer.h Network/Packets/ByteArray.cpp Network/Packets/ByteArray.h Network/Packets/PacketConsumer.h Network/Packets/PacketConsumers.h Network/Packets/IPacketConsumer.h Network/NetworkRemoteServer.h Network/PacketReceiver.h Network/PacketSender.h Network/NetServer.cpp Network/NetServer.h SystemHolder.h Network/Packets/PingPacket.cpp Network/Packets/PingPacket.h TimeUtil.cpp TimeUtil.h Network/Packets/HandshakePacket.cpp Network/Packets/HandshakePacket.h Network/Packets/HandshakeResponsePacket.cpp Network/Packets/HandshakeResponsePacket.h Network/Packets/PacketConsumerException.h Network/Packets/PlayerInfoPacket.cpp Network/Packets/PlayerInfoPacket.h Graphic/KeyCodes.h Network/Packets/PlayerMovePacket.cpp Network/Packets/PlayerMovePacket.h
        VelocitySystem.cpp Component/PhysicComponent.cpp Component/PhysicComponent.h Network/Packets/EntityVelocityPacket.cpp TickUtil.cpp TickUtil.h Network/Packets/EntityInfoPacket.cpp Network/Packets/EntityInfoPacket.h Network/Packets/PlayerShootPacket.cpp Network/Packets/PlayerShootPacket.h Network/Packets/EntityDestroyPacket.cpp Network/Packets/EntityDestroyPacket.h EntityUtils.cpp ColliderHitboxSystem.cpp Hitbox.cpp Hitbox.h Component/ColliderComponent.cpp Rectangle.cpp Rectangle.h Graphic/SpriteSheet.h Graphic/SpriteProperty.cpp Graphic/SpriteProperty.h Graphic/SpriteSheet.cpp Network/Packets/ProjectileHitPacket.cpp Network/Packets/ProjectileHitPacket.h EngineTypes.h
        Component/PlayerInfoComponent.cpp Registry.h Vector2i.cpp Component/PositionComponent.cpp engineLua/LuaWrapper.cpp engineLua/LuaWrapper.h engineLua/LuaEntityType.cpp engineLua/LuaEntityType.h engineLua/LuaEntityTypeFactory.cpp engineLua/LuaEntityTypeFactory.h engineLua/LuaLoader.cpp engineLua/LuaLoader.h Component/EntityTypeComponent2.cpp Component/EntityTypeComponent2.h StringRegistry.h Graphic/Sprite.cpp Graphic/Sprite.h CountRegistry.h engineLua/LuaComponentFactory.cpp engineLua/LuaComponentFactory.h
        Component/CooldownComponent.cpp Component/IAComponent.h)

target_link_libraries(eng lua_static)