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

#include "LobbyScene.h"
#include "TextComponent.h"
#include "PlayGameSystem.h"
#include "Engine/engineLua/LuaLevelFactory.h"
#include "Client/Textures/CreateButton.h"
#include "EntityLinkComponent.h"

static void toNextLevel(EnginePtr engine,std::shared_ptr<Entity> entity)
{
    auto levels = engine->getModule<LuaLevelFactory>();
    auto levelNameEntity = entity->getComponent<EntityLinkComponent>()->entity;
    if (levelNameEntity != nullptr) {
        int level = (levels->getSelectedLevel() + 1) % (int)levels->getLevels().size();
        levels->setSelectedLevel(level);
        levelNameEntity->getComponent<TextComponent>()->setText(levels->getLevels()[levels->getSelectedLevel()]->getName());
    }
}

static void toPreviousLevel(EnginePtr engine,std::shared_ptr<Entity> entity)
{
    auto levels = engine->getModule<LuaLevelFactory>();
    auto levelNameEntity = entity->getComponent<EntityLinkComponent>()->entity;
    if (levelNameEntity != nullptr) {
        int level = (levels->getSelectedLevel() - 1) % (int)levels->getLevels().size();
        levels->setSelectedLevel(level);
        levelNameEntity->getComponent<TextComponent>()->setText(levels->getLevels()[levels->getSelectedLevel()]->getName());
    }
}

std::shared_ptr<Scene> lobbyScene(EnginePtr engine){
    auto sc = engine->createScene<Scene>();
    auto lib = engine->getModule<IGraphicLib>();
    auto height = lib->getWindow().getHeight();
    auto width = lib->getWindow().getWidth();
    auto levels = engine->getModule<LuaLevelFactory>();

    auto background = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_1,-1);
    auto fourthground = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_2,-2);
    auto thirdground = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_3,-2);
    auto secondground = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_4,-3);
    auto firstground = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_5,-4);

    auto title = sc->createEntity();
    title->addComponent<PositionComponent>((width / 2) - 350, (height / 3) - (600 / 2));
    auto titleText = title->addComponent<TextComponent>("Waiting for players ...",75);
    titleText->setColor(ColorCodes::COLOR_ORANGE);


    auto select = sc->createEntity();
    select->addComponent<PositionComponent>((width / 2) - 150, height / 2 - (400 / 2));
    auto selectText = select->addComponent<TextComponent>("Select a level : ", 50);
    selectText->setColor(ColorCodes::COLOR_ORANGE);

    auto sceneSelector = sc->createEntity();
    auto levelName = sceneSelector->addComponent<TextComponent>(levels->getLevels()[levels->getSelectedLevel()]->getName(), 45);
    auto levelNamePos = sceneSelector->addComponent<PositionComponent>((width / 2) - 50, height / 2);
    levelName->setColor(ColorCodes::COLOR_ORANGE);

    auto nextLevel = createButton(lib, sc,(width / 2) + 50, (height / 2) + 150,Textures::ARROW_RIGHT, toNextLevel);
    nextLevel->addComponent<EntityLinkComponent>(sceneSelector);

    auto previous = createButton(lib, sc,(width / 2) - 75, (height / 2) + 150,Textures::ARROW_LEFT, toPreviousLevel);
    previous->addComponent<EntityLinkComponent>(sceneSelector);


    auto instruction = sc->createEntity();
    instruction->addComponent<PositionComponent>((width / 2) - 350, (height / 2) + (150 * 2));
    auto instructionText = instruction->addComponent<TextComponent>("Press Space to start the game", 50);
    instructionText->setColor(ColorCodes::COLOR_ORANGE);

    sc->addSystem<PlayGameSystem>();
    sc->addSystem<VelocitySystem>();
    return sc;
}