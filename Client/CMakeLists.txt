cmake_minimum_required(VERSION 3.16)
project(r-type-client)

add_executable(r-type-client
        main.cpp

        Textures/CreateButton.cpp
        Textures/CreateScrollingTexture.cpp
        Textures/Textures.cpp
        Textures/createFixTexture.cpp
        Textures/CreateHud.cpp
        Textures/LifeComponent.cpp
        Textures/LifeSystem.cpp
        Textures/HudCooldownComponent.cpp
        Textures/CooldownSystem.cpp

        Consumers/PingPacketConsumer.cpp
        Consumers/HandshakeResponseConsumer.cpp
        Consumers/PlayerInfoConsumer.cpp
        Consumers/EntityInfoConsumer.cpp
        Consumers/EntityDestroyConsumer.cpp
        Consumers/EntityVelocityPacketConsumer.cpp
        Consumers/ProjectileHitConsumer.cpp
        Consumers/DamageConsumer.cpp
        Consumers/StartGameConsumer.cpp
        Consumers/PacketWinConsumer.cpp
        Consumers/PacketSwitchWeaponConsumer.cpp

        Player/PlayerKeysSystem.cpp
        Player/Player.cpp
        Player/PlayerMoveSystem.cpp
        Player/PlayerShootSystem.cpp

        MainMenu.cpp
        StayAliveSystem.cpp
        AnimationComponent.cpp 
        AnimationSystem.cpp
        MouseSystem.cpp 
        ButtonComponent.cpp  
        GameScene.cpp
        Sounds.cpp
        Scenes.cpp
        ClientNetServer.cpp

        ipScene.cpp
        TextBoxComponent.cpp
        TextBoxSystem.cpp
        CreateTextBox.cpp
        EntityLinkComponent.cpp
        OptionScene.cpp
        Musics.cpp
        TextComponent.cpp
        TextSystem.cpp


        LobbyScene.cpp
        PlayGameSystem.cpp

        BossCreatorClient.cpp

        Consumers/ScoreConsumer.cpp
        ScoreComponent.cpp)


target_link_libraries(r-type-client eng engine-raylib)
if(WIN32)
    target_link_libraries(r-type-client wsock32 ws2_32 -static)
else()
    target_link_libraries(r-type-client -static-libgcc -static-libstdc++ -lpthread)
endif()
