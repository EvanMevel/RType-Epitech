cmake_minimum_required(VERSION 3.16)
project(r-type-server)

add_executable(r-type-server
        main.cpp

        Consumers/PingPacketConsumer.cpp
        Consumers/HandshakeConsumer.cpp
        Consumers/PlayerMoveConsumer.cpp
        Consumers/PlayerShootConsumer.cpp
        Consumers/StartGameConsumer.cpp

        ClientData.cpp
        RTypeServer.cpp
        TimeoutSystem.cpp
        ServerVelocitySystem.cpp
        ProjectileCleanupSystem.cpp
        EnemyRandomSpawnSystem.cpp
        EnemyShootSystem.cpp
        PacketSendingScene.cpp
        EnemyInfoComponent.cpp
        Levels.cpp
        PlayerList.cpp

        LevelSystem.cpp
        SynchronizedWeapon.cpp
        BossSystem.cpp
        BossCreatorServer.cpp ServerCollectableModule.cpp ServerCollectableModule.h)


target_link_libraries(r-type-server eng)
if(WIN32)
    target_link_libraries(r-type-server wsock32 ws2_32 -static)
else()
    target_link_libraries(r-type-server -static-libgcc -static-libstdc++ -lpthread)
endif()