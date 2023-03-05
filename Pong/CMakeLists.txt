cmake_minimum_required(VERSION 3.16)
project(pong)

add_executable(pong
        main.cpp

        ButtonComponent.cpp

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


target_link_libraries(pong engine-raylib)

if(WIN32)
    target_link_libraries(pong ws2_32 -static)
else()
    target_link_libraries(pong -static-libgcc -static-libstdc++ -lpthread)
endif()