cmake_minimum_required(VERSION 3.16)
project(r-type-server)

add_executable(r-type-server
        main.cpp

        Consumers/PingPacketConsumer.cpp
        Consumers/HandshakeConsumer.cpp
        Consumers/PlayerMoveConsumer.cpp
        Consumers/PlayerShootConsumer.cpp

        ClientData.cpp
        RTypeServer.cpp
        TimeoutSystem.cpp
        ServerVelocitySystem.cpp
        ProjectileCleanupSystem.cpp
        EnemyRandomSpawnSystem.cpp
        EnemyShootSystem.cpp
        ServerColliderSystem.cpp
        PacketSendingScene.cpp
        EnemyInfoComponent.cpp
        Levels.cpp
        PlayerList.cpp)