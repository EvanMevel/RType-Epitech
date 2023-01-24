cmake_minimum_required(VERSION 3.24)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(Component)

add_library(eng
        Component/AccelerationComponent.cpp
        Component/AccelerationComponent.h
        Component/EntityTypeComponent.cpp
        Component/EntityTypeComponent.h
        Component/HealthComponent.cpp
        Component/HealthComponent.h
        Component/HitboxComponent.cpp
        Component/HitboxComponent.h
        Component/PositionComponent.cpp
        Component/PositionComponent.h
        Component/TeamComponent.cpp
        Component/TeamComponent.h
        Component/VelocityComponent.cpp
        Component/VelocityComponent.h
        Component/IComponent.h

        Engine.cpp
        Engine.h
        Entity.cpp
        Entity.h
        IConsumer.h
        Network/Packets/IPacket.h
        ISystem.h
        Scene.cpp
        Scene.h Graphic/Vector2f.cpp Graphic/Vector2f.h Graphic/Vector2i.cpp Graphic/IGraphicLib.cpp Graphic/IGraphicLib.h Graphic/Events/IEvent.h Graphic/IWindow.h Graphic/ITexture.h Graphic/ColorCodes.h EntityType.h ISystem.cpp EntityManager.cpp EntityManager.h Network/CrossPlatformSocket.cpp Network/CrossPlatformSocket.h Network/NetworkListener.cpp Network/NetworkListener.h Network/Packets/PacketSerializer.h Network/Packets/ByteArray.cpp Network/Packets/ByteArray.h Network/Packets/TestPacket.cpp Network/Packets/TestPacket.h Network/Packets/PacketConsumer.h Network/Packets/PacketConsumers.h Network/Packets/IPacketConsumer.h Network/NetworkRemoteServer.cpp Network/NetworkRemoteServer.h Network/PacketReceiver.h Network/PacketSender.h Network/NetServer.cpp Network/NetServer.h SystemHolder.h Network/Packets/EntityTestPacket.h Network/Packets/PingPacket.cpp Network/Packets/PingPacket.h TimeUtil.cpp TimeUtil.h)