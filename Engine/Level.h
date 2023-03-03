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

class LevelEnemy {
private:
    std::string _type;
    int _x;
    int _y;
public:
    LevelEnemy(const std::string &type, int x, int y);

    [[maybe_unused]] const std::string &getType() const;

    int getX() const;

    int getY() const;
};

class Level {
private:
    std::vector<LevelEnemy> _enemies;
    std::string _name;

public:
    explicit Level(const std::string &name);

    void spawn(EnginePtr engine, const LevelEnemy &enemy);

    void update(int x, EnginePtr engine);

    void addEnemy(const std::string &type, int x, int y);

    const std::string &getName() const;
};


#endif //R_TYPE_CLIENT_LEVEL_H