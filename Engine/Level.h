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

#ifndef R_TYPE_CLIENT_LEVEL_H
#define R_TYPE_CLIENT_LEVEL_H

#include <string>
#include <vector>
#include "Engine/EngineTypes.h"

/**
 * @brief Class that represents a level object (enemy, collectable, obstacle)
 */
class LevelObject {
private:
    std::string _type;
    int _x;
    int _y;
public:
    LevelObject(const std::string &type, int x, int y);

    [[maybe_unused]] const std::string &getType() const;

    int getX() const;

    int getY() const;
};

/**
 * @brief Class that represents a level
 */
class Level {
private:
    std::vector<LevelObject> _objects;
    std::string _name;
    std::size_t _end;

public:
    explicit Level(const std::string &name);

    Level(const std::string &name, size_t end);

    void spawn(EnginePtr engine, const LevelObject &obj);

    virtual bool update(int x, EnginePtr engine);

    void addObject(const std::string &type, int x, int y);

    const std::string &getName() const;
};


#endif //R_TYPE_CLIENT_LEVEL_H
