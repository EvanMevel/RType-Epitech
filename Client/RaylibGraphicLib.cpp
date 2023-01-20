//
// Created by evans on 18/01/2023.
//

#include "RaylibGraphicLib.h"
#include "raylib.h"
#include "RaylibTexture.h"

IWindow &RaylibGraphicLib::createWindow(int width, int height, std::string title) {
    InitWindow(width, height, title.c_str());
    this->window.setColors(colors);
    return this->window;
}

IWindow &RaylibGraphicLib::getWindow() {
    return this->window;
}

void RaylibGraphicLib::drawText(std::string string, int x, int y, int size, ColorCodes color) {
    DrawText(string.c_str(), x, y, size, GREEN);
}

void RaylibGraphicLib::closeWindow() {
    CloseWindow();
}

ITexture RaylibGraphicLib::createTexture(const std::string &texturePath) {
    return RaylibTexture(texturePath);
}

void RaylibGraphicLib::drawTexture(ITexture texture, int x, int y, ColorCodes code) {
    auto texture2D = any_cast<Texture2D>(texture.handle);
    DrawTexture(texture2D, x, y, colors[code]);
}

std::vector<std::any> RaylibGraphicLib::retrieveEvents() {
    return std::vector<std::any>();
}

RaylibGraphicLib::RaylibGraphicLib() {
    colors[ColorCodes::COLOR_WHITE] = WHITE;
    colors[ColorCodes::COLOR_BLACK] = BLACK;
    colors[ColorCodes::COLOR_RED] = RED;
    colors[ColorCodes::COLOR_GREEN] = GREEN;
    colors[ColorCodes::COLOR_BLUE] = BLUE;
    colors[ColorCodes::COLOR_YELLOW] = YELLOW;
}
