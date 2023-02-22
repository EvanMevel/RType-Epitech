// MIT License
//
// Copyright (c) 2023 Audrey Amar, Théo Guguen, Evan Mevel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "RaylibGraphicLib.h"
#include "RaylibTexture.h"
#include "RaylibAnimation.h"
#include "RaylibMusic.h"
#include "RaylibSound.h"

RaylibGraphicLib::RaylibGraphicLib() {
    colors[ColorCodes::COLOR_WHITE] = ray::WHITE;
    colors[ColorCodes::COLOR_BLACK] = ray::BLACK;
    colors[ColorCodes::COLOR_RED] = ray::RED;
    colors[ColorCodes::COLOR_GREEN] = ray::GREEN;
    colors[ColorCodes::COLOR_BLUE] = ray::BLUE;
    colors[ColorCodes::COLOR_YELLOW] = ray::YELLOW;
}

IWindow &RaylibGraphicLib::createWindow(int width, int height, std::string title) {
    ray::InitWindow(width, height, title.c_str());
    this->window.setColors(colors);
    return this->window;
}

IWindow &RaylibGraphicLib::getWindow() {
    return this->window;
}

void RaylibGraphicLib::closeWindow() {
    ray::CloseWindow();
}

Texture RaylibGraphicLib::createTexture(const std::string &texturePath) {
    char *rtypeAssetsPath = std::getenv("RTYPE_ASSETS_PATH");
    std::string assetsPath = rtypeAssetsPath ? rtypeAssetsPath : "assets/";
    return std::make_shared<RaylibTexture>(assetsPath + texturePath);
}

void RaylibGraphicLib::drawText(std::string string, int x, int y, int size, ColorCodes color) {
    ray::DrawText(string.c_str(), x, y, size, colors[color]);
}

void RaylibGraphicLib::drawTextureEx(Texture &texture, int x, int y, float rotation, float scale,ColorCodes code) {
    auto texture2D = any_cast<ray::Texture2D>(texture->handle);
    ray::DrawTextureEx(texture2D, (ray::Vector2) {(float) x, (float) y}, rotation,scale, colors[code]);
}

void RaylibGraphicLib::drawTexture(Texture &texture, int x, int y, ColorCodes code) {
    auto texture2D = any_cast<ray::Texture2D>(texture->handle);
    ray::DrawTexture(texture2D, x, y, colors[code]);
}

void RaylibGraphicLib::drawSprite(std::shared_ptr<Sprite> sprite, int x, int y, ColorCodes codes) {
    auto texture2D = any_cast<ray::Texture2D>(sprite->spriteProperty->texture->handle);
    Rectangle rec = sprite->currentRect;
    ray::Rectangle sourceRec = {(float) rec.x, (float) rec.y,
                                (float) rec.width, (float) rec.height};
    float width = (float) rec.width * sprite->spriteProperty->scale;
    float height = (float) rec.height * sprite->spriteProperty->scale;
    ray::Rectangle destRec = {
            (float) x + (float) width / 2.0f,
            (float) y + (float) height / 2.0f,
            (float) width,
            (float) height
    };
    ray::Vector2 origin = {
            (float) width / 2.0f,
            (float) height / 2.0f
    };
    ray::DrawTexturePro(texture2D, sourceRec, destRec, origin, 0.0f, colors[codes]);
}

std::shared_ptr<IAnimation> RaylibGraphicLib::createAnimation(const std::string &texturePath) {
    char *rtypeAssetsPath = std::getenv("RTYPE_ASSETS_PATH");
    std::string assetsPath = rtypeAssetsPath ? rtypeAssetsPath : "assets/";
    return std::make_shared<RaylibAnimation>(assetsPath + texturePath);
}

void RaylibGraphicLib::drawAnimation(std::shared_ptr<IAnimation> animation, int x, int y, ColorCodes codes) {
    auto texture2D = any_cast<ray::Texture2D>(animation->texture);
    ray::DrawTexture(texture2D, x, y, colors[codes]);
}

IMouse &RaylibGraphicLib::getMouse() {
    return this->mouse;
}

bool RaylibGraphicLib::isKeyDown(KeyCodes code) {
    return ray::IsKeyDown(code);
}

void RaylibGraphicLib::initAudio() {
    ray::InitAudioDevice();
}

std::shared_ptr<IMusic> RaylibGraphicLib::createMusic(const std::string &musicPath) {
    char *rtypeAssetsPath = std::getenv("RTYPE_ASSETS_PATH");
    std::string assetsPath = rtypeAssetsPath ? rtypeAssetsPath : "assets/";
    return std::make_shared<RaylibMusic>(assetsPath + musicPath);
}

void RaylibGraphicLib::playMusic(std::shared_ptr<IMusic> music) {
    ray::Music raylibMusic = std::any_cast<ray::Music>(music->music);
    ray::PlayMusicStream(raylibMusic);
}

std::shared_ptr<ISound> RaylibGraphicLib::createSound(const std::string &soundPath) {
    char *rtypeAssetsPath = std::getenv("RTYPE_ASSETS_PATH");
    std::string assetsPath = rtypeAssetsPath ? rtypeAssetsPath : "assets/";
    return std::make_shared<RaylibSound>(assetsPath + soundPath);
}

void RaylibGraphicLib::playSound(std::shared_ptr<ISound> sound) {
    ray::Sound raylibSound = std::any_cast<ray::Sound>(sound->sound);
    ray::PlaySound(raylibSound);
}

void RaylibGraphicLib::drawRectangle(int posX, int posY, int width, int height, ColorCodes color) {
    ray::DrawRectangle(posX, posY, width ,height, colors[color]);
}

int RaylibGraphicLib::getCharPressed() {
    return ray::GetCharPressed();
}

bool RaylibGraphicLib::isKeyPressed(int key) {
    return ray::IsKeyPressed(key);
}
