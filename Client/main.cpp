//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Graphic/IGraphicLib.h"
#include "RaylibGraphicLib.h"

int main()
{
    Engine e;
    RaylibGraphicLib lib = RaylibGraphicLib();
    IWindow &window = lib.createWindow(500, 500, "teststs");
    while (!window.shouldClose()) {
        window.beginDrawing();
        window.setBackground(ColorCodes::COLOR_WHITE);
        window.endDrawing();
    }
}