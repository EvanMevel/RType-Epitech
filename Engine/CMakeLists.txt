cmake_minimum_required(VERSION 3.24)
project(Engine)

set(CMAKE_CXX_STANDARD 17)

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
        Component/IComponent.cpp
        Component/IComponent.h

        Engine.cpp
        Engine.h
        Entity.cpp
        Entity.h
        IConsumer.h
        IPacket.cpp
        IPacket.h
        ISocket.cpp
        ISocket.h
        ISystem.h
        PacketDeserializer.cpp
        PacketDeserializer.h
        PacketSerializer.cpp
        PacketSerializer.h
        Scene.cpp
        Scene.h)