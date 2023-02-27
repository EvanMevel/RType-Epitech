
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

        )
