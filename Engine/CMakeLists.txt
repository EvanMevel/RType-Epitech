cmake_minimum_required(VERSION 3.16)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

set(LUA_ENABLE_TESTING OFF)
add_subdirectory(lua)
get_filename_component(LUA_INCLUDE_DIR lua/lua-5.4.4/include REALPATH)
set(LUA_LIBRARIES lua_static)

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
        Network/Packets/StartGamePacket.cpp
        Network/Packets/PacketWin.cpp
        Network/Packets/PacketSwitchWeapon.cpp

        Graphic/IGraphicLib.cpp
        Graphic/SpriteProperty.cpp
        Graphic/SpriteSheet.cpp
        Graphic/Sprite.cpp

        Graphic/Sprites/DrawSpriteSystem.cpp
        Graphic/Sprites/SpriteComponent.cpp

        Graphic/Textures/DrawFixTextureSystem.cpp
        Graphic/Textures/DrawTextureNameSystem.cpp
        Graphic/Textures/FixTextureComponent.cpp
        Graphic/Textures/ScrollingTextureComponent.cpp
        Graphic/Textures/ScrollingTextureSystem.cpp
        Graphic/Textures/TextureNameComponent.cpp

        
        Component/PhysicComponent.cpp
        Component/EntityTypeComponent2.cpp
        Component/ColliderComponent.cpp
        Component/PlayerInfoComponent.cpp
        Component/PositionComponent.cpp
        Component/CooldownComponent.cpp
        Component/HealthComponent.cpp
        Component/HitboxComponent.cpp
        Component/TeamComponent.cpp
        Component/ProjectileComponent.cpp
        Component/WeaponComponent.cpp
        Component/InanimateComponent.cpp
        Component/CollectableComponent.cpp

        engineLua/LuaWrapper.cpp
        engineLua/LuaEntityType.cpp
        engineLua/LuaEntityTypeFactory.cpp
        engineLua/LuaLoader.cpp
        engineLua/LuaComponentFactory.cpp
        engineLua/LuaClass.cpp
        engineLua/LuaType.cpp
        engineLua/LuaLevelFactory.cpp
        engineLua/LuaWeaponFactory.cpp

        EntityManager.cpp
        TimeUtil.cpp
        VelocitySystem.cpp
        TickUtil.cpp
        EntityUtils.cpp
        ColliderHitboxSystem.cpp
        Hitbox.cpp
        Rectangle.cpp
        Vector2i.cpp

        Level.cpp

        Weapon.cpp

        BossCreator.cpp
        CollectableModule.cpp

        Network/Packets/ScorePacket.cpp
        )

target_link_libraries(eng lua_static)
