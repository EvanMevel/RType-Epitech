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

#include "IGraphicLib.h"
#include "Engine.h"


IGraphicLib::~IGraphicLib() {

}

std::vector<std::function<void()>> &IGraphicLib::getExecs() {
    return execs;
}

std::shared_ptr<SpriteSheet> IGraphicLib::createSpriteSheet(const std::string &texturePath) {
    return std::make_shared<SpriteSheet>(createTexture(texturePath));
}

const std::unique_ptr<Registry<ITexture>> &IGraphicLib::getTextures() {
    return _textures;
}

const std::unique_ptr<StringRegistry<SpriteProperty>> &IGraphicLib::getSpriteProperties() {
    return _spriteProperties;
}

const std::unique_ptr<Registry<ISound>> &IGraphicLib::getSounds() {
    return _sounds;
}

std::vector<std::shared_ptr<SpriteSheet>> &IGraphicLib::getSpriteSheets() {
    return spriteSheets;
}

const std::unique_ptr<CountRegistry<Sprite>> &IGraphicLib::getSprites() const {
    return _sprites;
}

const std::shared_ptr<IMusic> &IGraphicLib::getMusic() const {
    return _music;
}

void IGraphicLib::setMusic(const std::shared_ptr<IMusic> &music) {
    _music = music;
}

const std::unique_ptr<Registry<IMusic>> &IGraphicLib::getMusics() const {
    return _musics;
}

float IGraphicLib::getVolume() const {
    return _volume;
}

void IGraphicLib::setVolume(float volume) {
    _volume = volume;
}
