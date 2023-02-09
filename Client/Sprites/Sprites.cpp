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

#include "Sprites.h"

void loadSprites(const std::shared_ptr<IGraphicLib> &lib) {
    const std::unique_ptr<Registry<Sprite>> &spriteRegistry = lib->getSprites();
    auto playerSpriteSheet = lib->createSpriteSheet("assets/r-typesheet42.gif");

    spriteRegistry->registerValue(Sprites::PLAYER_1,
                                  playerSpriteSheet->createSprite(0, 3, 33, 14, 5, 0, 30, 4.0f));
    spriteRegistry->registerValue(Sprites::PLAYER_2,
                                  playerSpriteSheet->createSprite(0, 20, 33, 14, 5, 0, 30, 4.0f));
    spriteRegistry->registerValue(Sprites::PLAYER_3,
                                  playerSpriteSheet->createSprite(0, 37, 33, 14, 5, 0, 30, 4.0f));
    spriteRegistry->registerValue(Sprites::PLAYER_4,
                                  playerSpriteSheet->createSprite(0, 54, 33, 14, 5, 0, 30, 4.0f));

    auto projSpriteSheet = lib->createSpriteSheet("assets/r-typesheet1.gif");

    auto projSprite = projSpriteSheet->createSprite(103, 170, 81, 16, 2, 0, 30);
    auto projSprite2 = projSpriteSheet->createSprite(267, 170, 81, 16, 2, 0, 30);
    spriteRegistry->registerValue(Sprites::PROJECTILE_1, projSprite);
    spriteRegistry->registerValue(Sprites::PROJECTILE_2, projSprite2);


    auto enemySpriteSheet = lib->createSpriteSheet("assets/r-typesheet23.gif");

    auto enemySprite = enemySpriteSheet->createSprite(0, 6, 33, 22, 8, 0, 30, 3.0f);
    spriteRegistry->registerValue(Sprites::ENEMY_1, enemySprite);

    auto enemySpriteSheet2 = lib->createSpriteSheet("assets/r-typesheet7.gif");
    auto enemySprite2 = enemySpriteSheet2->createSprite(1, 34, 33, 32, 3, 0, 30, 3.0f);

    spriteRegistry->registerValue(Sprites::ENEMY_2, enemySprite2);
}