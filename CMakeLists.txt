cmake_minimum_required(VERSION 3.24)
project(B_CPP_500_REN_5_2_rtype_audrey_amar)

set(CMAKE_CXX_STANDARD 17)

include_directories(Engine)
include_directories(Engine/Component)

add_executable(B_CPP_500_REN_5_2_rtype_audrey_amar
        Engine/Component/AccelerationComponent.cpp
        Engine/Component/AccelerationComponent.h
        Engine/Component/EntityTypeComponent.cpp
        Engine/Component/EntityTypeComponent.h
        Engine/Component/HealthComponent.cpp
        Engine/Component/HealthComponent.h
        Engine/Component/HitboxComponent.cpp
        Engine/Component/HitboxComponent.h
        Engine/Component/PositionComponent.cpp
        Engine/Component/PositionComponent.h
        Engine/Component/TeamComponent.cpp
        Engine/Component/TeamComponent.h
        Engine/Component/VelocityComponent.cpp
        Engine/Component/VelocityComponent.h
        Engine/Component/IComponent.cpp
        Engine/Component/IComponent.h

        Engine/Engine.cpp
        Engine/Engine.h
        Engine/Entity.cpp
        Engine/Entity.h
        Engine/IConsumer.h
        Engine/IPacket.cpp
        Engine/IPacket.h
        Engine/ISocket.cpp
        Engine/ISocket.h
        Engine/ISystem.h
        Engine/PacketDeserializer.cpp
        Engine/PacketDeserializer.h
        Engine/PacketSerializer.cpp
        Engine/PacketSerializer.h
        Engine/Scene.cpp
        Engine/Scene.h)
