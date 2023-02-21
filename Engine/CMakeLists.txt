cmake_minimum_required(VERSION 3.16)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

option(LUA_ENABLE_TESTING "Build and run tests" OFF)
add_subdirectory(lua)

include_directories(.)
include_directories(Component)

add_library(eng
        Engine.cpp
        Entity.cpp
        Scene.cpp
        ISystem.cpp

        Network/CrossPlatformSocket.cpp
        Network/NetworkListener.cpp
        Network/NetServer.cpp

        Network/Packets/ByteArray.cpp
        Network/Packets/PingPacket.cpp
        Network/Packets/HandshakePacket.cpp
        Network/Packets/HandshakeResponsePacket.cpp
        Network/Packets/PlayerInfoPacket.cpp
        Network/Packets/PlayerMovePacket.cpp
        Network/Packets/EntityInfoPacket.cpp
        Network/Packets/PlayerShootPacket.cpp
        Network/Packets/EntityDestroyPacket.cpp
        Network/Packets/EntityVelocityPacket.cpp
        Network/Packets/ProjectileHitPacket.cpp
        Network/Packets/DamagePacket.cpp

        Graphic/IGraphicLib.cpp
        Graphic/SpriteProperty.cpp
        Graphic/SpriteSheet.cpp
        Graphic/Sprite.cpp

        Component/PhysicComponent.cpp
        Component/EntityTypeComponent2.cpp
        Component/ColliderComponent.cpp
        Component/PlayerInfoComponent.cpp
        Component/PositionComponent.cpp
        Component/CooldownComponent.cpp
        Component/HealthComponent.cpp
        Component/HitboxComponent.cpp
        Component/TeamComponent.cpp

        engineLua/LuaWrapper.cpp
        engineLua/LuaEntityType.cpp
        engineLua/LuaEntityTypeFactory.cpp
        engineLua/LuaLoader.cpp
        engineLua/LuaComponentFactory.cpp

        EntityManager.cpp
        TimeUtil.cpp
        VelocitySystem.cpp
        TickUtil.cpp
        EntityUtils.cpp
        ColliderHitboxSystem.cpp
        Hitbox.cpp
        Rectangle.cpp
        Vector2i.cpp)

target_link_libraries(eng lua_static)