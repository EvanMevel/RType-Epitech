//
// Created by evans on 18/01/2023.
//

#include "RaylibGraphicLib.h"
#include "RaylibTexture.h"
#include "RaylibAnimation.h"

IWindow &RaylibGraphicLib::createWindow(int width, int height, std::string title) {
    ray::InitWindow(width, height, title.c_str());
    this->window.setColors(colors);
    return this->window;
}

IWindow &RaylibGraphicLib::getWindow() {
    return this->window;
}

void RaylibGraphicLib::drawText(std::string string, int x, int y, int size, ColorCodes color) {
    ray::DrawText(string.c_str(), x, y, size, colors[color]);
}

void RaylibGraphicLib::closeWindow() {
    ray::CloseWindow();
}

ITexture RaylibGraphicLib::createTexture(const std::string &texturePath) {
    return RaylibTexture(texturePath);
}

void RaylibGraphicLib::drawTexture(ITexture texture, int x, int y, ColorCodes code) {
    auto texture2D = any_cast<ray::Texture2D>(texture.handle);
    ray::DrawTexture(texture2D, x, y, colors[code]);
}

std::vector<std::any> RaylibGraphicLib::retrieveEvents() {
    return std::vector<std::any>();
}

RaylibGraphicLib::RaylibGraphicLib() {
    colors[ColorCodes::COLOR_WHITE] = ray::WHITE;
    colors[ColorCodes::COLOR_BLACK] = ray::BLACK;
    colors[ColorCodes::COLOR_RED] = ray::RED;
    colors[ColorCodes::COLOR_GREEN] = ray::GREEN;
    colors[ColorCodes::COLOR_BLUE] = ray::BLUE;
    colors[ColorCodes::COLOR_YELLOW] = ray::YELLOW;

    keys[KeyCodes::KEY_A] = ray::KEY_A;
    keys[KeyCodes::KEY_B] = ray::KEY_B;
    keys[KeyCodes::KEY_C] = ray::KEY_C;
    keys[KeyCodes::KEY_UP] = ray::KEY_UP;
    keys[KeyCodes::KEY_DOWN] = ray::KEY_DOWN;
    keys[KeyCodes::KEY_LEFT] = ray::KEY_LEFT;
    keys[KeyCodes::KEY_RIGHT] = ray::KEY_RIGHT;
    keys[KeyCodes::KEY_SPACE] = ray::KEY_SPACE;
}

bool RaylibGraphicLib::isKeyDown(KeyCodes code) {
    ray::KeyboardKey key = keys[code];
    return ray::IsKeyDown(key);
}

std::shared_ptr<IAnimation> RaylibGraphicLib::createAnimation(const std::string &texturePath) {
    return std::make_shared<RaylibAnimation>(texturePath);
}

void RaylibGraphicLib::drawAnimation(std::shared_ptr<IAnimation> animation, int x, int y, ColorCodes codes) {
    auto texture2D = any_cast<ray::Texture2D>(animation->texture);
    ray::DrawTexture(texture2D, x, y, colors[codes]);
}
