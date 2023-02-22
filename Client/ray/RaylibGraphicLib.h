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

#ifndef R_TYPE_SERVER_RAYLIBGRAPHICLIB_H
#define R_TYPE_SERVER_RAYLIBGRAPHICLIB_H

#include "Engine/Graphic/IGraphicLib.h"
#include "RaylibWindow.h"
#include "Engine/Graphic/ColorCodes.h"
#include "RaylibMouse.h"

/**
 * @brief Raylib implementation of IGraphicLib
 */
class RaylibGraphicLib : public IGraphicLib {
private:
    std::unordered_map<ColorCodes, ray::Color> colors;
    RaylibWindow window;
    RaylibMouse mouse;

public:
    RaylibGraphicLib();

    IWindow &createWindow(int width, int height, std::string title) override;

    void drawText(std::string string, int x, int y, int size, ColorCodes color) override;

    void drawRectangle(int posX, int posY, int width, int height, ColorCodes color) override;

    IWindow &getWindow() override;

    void closeWindow() override;

    Texture createTexture(const std::string &texturePath) override;

    void drawTexture(Texture &texture, int x, int y, ColorCodes codes) override;

    void drawTextureEx(Texture &texture, int x, int y, float rotation, float scale, ColorCodes codes) override;

    bool isKeyDown(KeyCodes codes) override;

    int getCharPressed() override;

    bool isKeyPressed(int key) override;

    std::shared_ptr<IAnimation> createAnimation(const std::string &texturePath) override;

    void drawAnimation(std::shared_ptr<IAnimation> animation, int x, int y, ColorCodes codes) override;

    IMouse &getMouse() override;

    void drawSprite(std::shared_ptr<Sprite> sprite, int x, int y, ColorCodes codes) override;

    void initAudio() override;

    std::shared_ptr<IMusic> createMusic(const std::string &musicPath) override;

    std::shared_ptr<ISound> createSound(const std::string &soundPath) override;

    void playMusic(std::shared_ptr<IMusic>) override;

    void playSound(std::shared_ptr<ISound> ptr) override;
};


#endif //R_TYPE_SERVER_RAYLIBGRAPHICLIB_H
