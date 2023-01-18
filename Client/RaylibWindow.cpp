//
// Created by evans on 18/01/2023.
//

#include "RaylibWindow.h"
#include "raylib.h"

bool RaylibWindow::shouldClose() {
    return WindowShouldClose();
}

void RaylibWindow::beginDrawing() {
    BeginDrawing();
}

void RaylibWindow::endDrawing() {
    EndDrawing();
}

void RaylibWindow::setTargetFPS(int i) {
    SetTargetFPS(i);
}

void RaylibWindow::setBackground(ColorCodes code) {
    ClearBackground(colors[code]);
}

void RaylibWindow::setColors(const std::unordered_map<ColorCodes, Color> &colors) {
    RaylibWindow::colors = colors;
}
