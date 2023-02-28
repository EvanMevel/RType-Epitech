
cmake_minimum_required(VERSION 3.16)
project(pong)

add_executable(pong
        main.cpp

        ray/RaylibGraphicLib.cpp 
        ray/RaylibWindow.cpp 
        ray/RaylibTexture.cpp
        ray/RaylibAnimation.cpp
        ray/RaylibMouse.cpp
        ray/RaylibMusic.cpp
        ray/RaylibSound.cpp

        ButtonComponent.cpp

        DrawFixTextureSystem.cpp

        FixTextureComponent.cpp

        GameScene.cpp
        MainMenu.cpp

        MouseSystem.cpp

        Scenes.cpp

        Sounds.cpp

        Textures.cpp

        PlayerComponent.cpp

        PlayerMoveSystem.cpp
        PlayerKeys.cpp
        PlayerKeysSystem.cpp
        PongVelocitySystem.cpp
        BallComponent.cpp
        BallBounceSystem.cpp
        WinConditionSystem.cpp

        )


target_link_libraries(pong eng raylib)

if(WIN32)
    target_link_libraries(pong ws2_32 -static)
else()
    target_link_libraries(pong -static-libgcc -static-libstdc++ -lpthread)
endif()