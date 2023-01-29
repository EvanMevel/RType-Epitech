//
// Created by evans on 18/01/2023.
//

#include "RaylibWindow.h"
#include "raylib.h"

bool RaylibWindow::shouldClose() {
    return ray::WindowShouldClose();
}

void RaylibWindow::beginDrawing() {
    ray::BeginDrawing();
}

void RaylibWindow::endDrawing() {
    ray::EndDrawing();
}

void RaylibWindow::setTargetFPS(int i) {
    ray::SetTargetFPS(i);
}

void RaylibWindow::setBackground(ColorCodes code) {
    ClearBackground(colors[code]);
}

void RaylibWindow::setColors(const std::unordered_map<ColorCodes, ray::Color> &colors) {
    RaylibWindow::colors = colors;
}

int RaylibWindow::getWidth() {
    return ray::GetScreenWidth();
}

int RaylibWindow::getHeight() {
    return ray::GetScreenHeight();
}
