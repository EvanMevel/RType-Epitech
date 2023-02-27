cmake_minimum_required(VERSION 3.16)
project(r-type-client)

add_executable(r-type-client
        main.cpp

        ray/RaylibGraphicLib.cpp 
        ray/RaylibWindow.cpp 
        ray/RaylibTexture.cpp
        ray/RaylibAnimation.cpp
        ray/RaylibMouse.cpp
        ray/RaylibMusic.cpp
        ray/RaylibSound.cpp

        Textures/FixTextureComponent.cpp 
        Textures/DrawFixTextureSystem.cpp 
        Textures/CreateButton.cpp
        Textures/ScrollingTextureComponent.cpp
        Textures/ScrollingTextureSystem.cpp
        Textures/CreateScrollingTexture.cpp
        Textures/Textures.cpp

        Consumers/PingPacketConsumer.cpp
        Consumers/HandshakeResponseConsumer.cpp
        Consumers/PlayerInfoConsumer.cpp
        Consumers/EntityInfoConsumer.cpp
        Consumers/EntityDestroyConsumer.cpp
        Consumers/EntityVelocityPacketConsumer.cpp
        Consumers/ProjectileHitConsumer.cpp

        Sprites/SpriteComponent.cpp
        Sprites/DrawSpriteSystem.cpp
        Sprites/Sprites.cpp

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
        TextBoxComponent.cpp TextBoxSystem.cpp TextBoxSystem.h CreateTextBox.cpp CreateTextBox.h EntityLinkComponent.cpp EntityLinkComponent.h)
