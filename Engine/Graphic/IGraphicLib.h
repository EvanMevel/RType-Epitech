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

#ifndef R_TYPE_SERVER_IGRAPHICLIB_H
#define R_TYPE_SERVER_IGRAPHICLIB_H

#include <unordered_map>
#include <typeindex>
#include <any>
#include <cstddef>
#include <string>
#include <functional>
#include "../IConsumer.h"
#include "IWindow.h"
#include "../SystemHolder.h"
#include "KeyCodes.h"
#include "IAnimation.h"
#include "IMouse.h"
#include "SpriteSheet.h"
#include "IMusic.h"
#include "ISound.h"

class Engine;

/**
 * @brief Interface representing a graphic library
 * @details This interface is used to abstract the graphic library used by the engine.
 * @details It is used by the engine to draw on the screen and to retrieve events from the user.
 */
class IGraphicLib : public SystemHolder {
private:
    std::unordered_map<std::type_index, std::any> modules;
    std::vector<std::function<void()>> execs;
public:
    virtual ~IGraphicLib();

    std::vector<std::function<void()>> &getExecs();

    virtual IWindow& createWindow(int width, int height, std::string title) = 0;
    virtual IWindow& getWindow() = 0;
    virtual void closeWindow() = 0;

    virtual std::shared_ptr<ITexture> createTexture(const std::string &texturePath) = 0;
    virtual void drawTexture(std::shared_ptr<ITexture>, int x, int y, ColorCodes) = 0;
    virtual void drawTextureEx(std::shared_ptr<ITexture>, int x, int y, float rotation, float scale, ColorCodes) = 0;

    std::shared_ptr<SpriteSheet> createSpriteSheet(const std::string &texturePath);
    virtual void drawSprite(std::shared_ptr<Sprite> sprite, int x, int y, ColorCodes codes) = 0;

    virtual std::shared_ptr<IAnimation> createAnimation(const std::string &texturePath) = 0;
    virtual void drawAnimation(std::shared_ptr<IAnimation> animation, int x, int y, ColorCodes codes) = 0;

    virtual void drawText(std::string, int x, int y, int size, ColorCodes) = 0;

    virtual bool isKeyDown(KeyCodes) = 0;

    virtual IMouse &getMouse() = 0;

    virtual void initAudio() = 0;
    virtual std::shared_ptr<IMusic> createMusic(const std::string &musicPath) = 0;
    virtual void playMusic(std::shared_ptr<IMusic>) = 0;
    virtual std::shared_ptr<ISound> createSound(const std::string &soundPath) = 0;
    virtual void playSound(std::shared_ptr<ISound>) = 0;

    template<class ...Args>
    void execOnLibThread(std::function<void(Args...)> func, Args... args) {
        auto fu = std::bind(func, args...);
        execs.push_back(fu);
    }
    template<class ...Args>
    void execOnLibThread(void (*func)(Args...), Args... args) {
        std::function<void(Args...)> fu = func;
        execOnLibThread(fu, args...);
    }
};

#endif //R_TYPE_SERVER_IGRAPHICLIB_H
