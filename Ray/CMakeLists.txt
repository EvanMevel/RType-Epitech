cmake_minimum_required(VERSION 3.16)
project(engine-raylib)

include_directories(.)

add_library(engine-raylib

        ray/RaylibGraphicLib.cpp 
        ray/RaylibWindow.cpp 
        ray/RaylibTexture.cpp
        ray/RaylibAnimation.cpp
        ray/RaylibMouse.cpp
        ray/RaylibMusic.cpp
        ray/RaylibSound.cpp

        )


target_link_libraries(engine-raylib eng raylib)
