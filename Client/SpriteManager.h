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

#ifndef R_TYPE_SERVER_SPRITEMANAGER_H
#define R_TYPE_SERVER_SPRITEMANAGER_H

#include <unordered_map>
#include "Engine/Graphic/Sprite.h"

enum class SpriteType {
    PLAYER_1 = 0,
    PLAYER_2 = 1,
    PLAYER_3 = 2,
    PLAYER_4 = 3,
    PROJECTILE_1 = 4,
    PROJECTILE_2 = 5,
    ENEMY_1 = 6,
    ENEMY_2 = 7,
};

/**
 * @brief SpriteManager contains all the sprites of the game
 */
class SpriteManager {
private:
    std::unordered_map<SpriteType, std::shared_ptr<Sprite>> _sprites;

public:
    SpriteManager();
    std::shared_ptr<Sprite> getSprite(SpriteType type);

    void addSprite(SpriteType type, std::shared_ptr<Sprite> sprite);
};


#endif //R_TYPE_SERVER_SPRITEMANAGER_H
