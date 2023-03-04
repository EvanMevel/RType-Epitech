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

#include "Level.h"
#include "Engine.h"

LevelObject::LevelObject(const std::string &type, int x, int y) : _type(type), _x(x), _y(y) {

}

[[maybe_unused]] const std::string &LevelObject::getType() const {
    return _type;
}

int LevelObject::getX() const {
    return _x;
}

int LevelObject::getY() const {
    return _y;
}

Level::Level(const std::string &name) : _name(name) {

}

void Level::spawn(std::unique_ptr<Engine> &engine, const LevelObject &obj) {
    engine->getScene()->createEntity(engine, obj.getType(), 1800, obj.getY());
}

void Level::update(int x, EnginePtr engine) {
    auto it = _objects.begin();
    while (it != _objects.end()) {
        if (it->getX() <= x) {
            spawn(engine, *it);
            it = _objects.erase(it);
        } else {
            return;
        }
    }
}

void Level::addObject(const std::string &type, int x, int y) {
    auto it = _objects.begin();
    while (it != _objects.end()) {
        if (it->getX() > x) {
            break;
        }
        it++;
    }
    _objects.insert(it, LevelObject{type, x, y});
}

const std::string &Level::getName() const {
    return _name;
}
