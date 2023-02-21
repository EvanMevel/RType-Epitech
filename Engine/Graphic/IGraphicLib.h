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
#include "Engine/Registry.h"
#include "Engine/StringRegistry.h"
#include "Sprite.h"
#include "Engine/CountRegistry.h"

class Engine;

using Texture = std::shared_ptr<ITexture>;

/**
 * @brief Interface representing a graphic library
 * @details This interface is used to abstract the graphic library used by the engine.
 * @details It is used by the engine to draw on the screen and to retrieve events from the user.
 */
class IGraphicLib : public SystemHolder {
private:
    std::unordered_map<std::type_index, std::any> modules;
    std::vector<std::function<void()>> execs;
    std::unique_ptr<Registry<ITexture>> _textures = std::make_unique<Registry<ITexture>>();
    std::unique_ptr<Registry<ISound>> _sounds = std::make_unique<Registry<ISound>>();
    std::vector<std::shared_ptr<SpriteSheet>> spriteSheets;
    std::unique_ptr<StringRegistry<SpriteProperty>> _spriteProperties = std::make_unique<StringRegistry<SpriteProperty>>();
    std::unique_ptr<CountRegistry<Sprite>> _sprites = std::make_unique<CountRegistry<Sprite>>();
public:
    virtual ~IGraphicLib();

    std::vector<std::function<void()>> &getExecs();

    virtual IWindow& createWindow(int width, int height, std::string title) = 0;
    virtual IWindow& getWindow() = 0;
    virtual void closeWindow() = 0;

    virtual Texture createTexture(const std::string &texturePath) = 0;

    template<class EnumType>
    void registerTexture(EnumType key, const std::string &texturePath) {
        _textures->registerValue(key, createTexture(texturePath));
    }

    virtual void drawTexture(Texture &texture, int x, int y, ColorCodes) = 0;
    virtual void drawTextureEx(Texture &texture, int x, int y, float rotation, float scale, ColorCodes) = 0;

    std::shared_ptr<SpriteSheet> createSpriteSheet(const std::string &texturePath);
    virtual void drawSprite(std::shared_ptr<Sprite> sprite, int x, int y, ColorCodes codes) = 0;

    virtual std::shared_ptr<IAnimation> createAnimation(const std::string &texturePath) = 0;
    virtual void drawAnimation(std::shared_ptr<IAnimation> animation, int x, int y, ColorCodes codes) = 0;

    virtual void drawText(std::string, int x, int y, int size, ColorCodes) = 0;

    virtual void drawRectangle(int posX, int posY, int width, int height,  ColorCodes color) = 0;

    virtual bool isKeyDown(KeyCodes) = 0;

    virtual int getCharPressed() = 0;

    virtual IMouse &getMouse() = 0;

    virtual void initAudio() = 0;
    virtual std::shared_ptr<IMusic> createMusic(const std::string &musicPath) = 0;
    virtual void playMusic(std::shared_ptr<IMusic>) = 0;

    virtual std::shared_ptr<ISound> createSound(const std::string &soundPath) = 0;

    template<class EnumType>
    void registerSound(EnumType key, const std::string &soundPath) {
        _sounds->registerValue(key, createSound(soundPath));
    }
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

    const std::unique_ptr<Registry<ITexture>> &getTextures();

    const std::unique_ptr<StringRegistry<SpriteProperty>> &getSpriteProperties();

    const std::unique_ptr<Registry<ISound>> &getSounds();

    std::vector<std::shared_ptr<SpriteSheet>> &getSpriteSheets();

    const std::unique_ptr<CountRegistry<Sprite>> &getSprites() const;

};

template<class SoundType>
void playSound(std::shared_ptr<IGraphicLib> lib, SoundType sound) {
    lib->playSound(lib->getSounds()->getValue(sound));
}

#endif //R_TYPE_SERVER_IGRAPHICLIB_H
