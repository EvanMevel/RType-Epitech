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

#include "OptionScene.h"
#include "TextComponent.h"
#include "EntityLinkComponent.h"
#include "Client/Textures/CreateScrollingTexture.h"


static void volumeUp(EnginePtr engine, std::shared_ptr<Entity> entity) {
    auto lib = engine->getModule<IGraphicLib>();
    lib->setVolume(lib->getVolume() + 0.05);
    if (lib->getVolume() >= 1.0)
        lib->setVolume(1.0);
    lib->setVolumeMusic(lib->getMusic(), lib->getVolume());
    auto volumeEntity = entity->getComponent<EntityLinkComponent>()->entity;
    if (volumeEntity != nullptr) {
        volumeEntity->getComponent<TextComponent>()->setText(std::to_string((int) (lib->getVolume() * 100)));
    }
}

static void volumeDown(EnginePtr engine, std::shared_ptr<Entity> entity) {
    auto lib = engine->getModule<IGraphicLib>();
    lib->setVolume(lib->getVolume() - 0.05);
    if (lib->getVolume() <= 0)
        lib->setVolume(0.0);
    lib->setVolumeMusic(lib->getMusic(), lib->getVolume());
    auto volumeEntity = entity->getComponent<EntityLinkComponent>()->entity;
    if (volumeEntity != nullptr) {
        volumeEntity->getComponent<TextComponent>()->setText(std::to_string((int) (lib->getVolume() * 100)));
    }

}

static void optionToMainMenu(EnginePtr engine, std::shared_ptr<Entity> entity) {
    auto sceneHolder = engine->getModule<SceneHolder>();
    auto sc = sceneHolder->getValue(Scenes::MAIN_MENU);
    engine->setScene(sc);
}

std::shared_ptr<Scene> optionScene(EnginePtr engine) {
    auto sc = engine->createScene<Scene>();
    auto lib = engine->getModule<IGraphicLib>();

    auto height = lib->getWindow().getHeight();
    auto width = lib->getWindow().getWidth();

    auto background = createFixTexture(sc,Textures::BACKGROUND_1,0,0,0.0,3);
    auto firstground = createFixTexture(sc,Textures::BACKGROUND_2,0,0,0.0,3);
    auto secondground = createFixTexture(sc,Textures::BACKGROUND_4,0,0,0.0,3);

    auto title = sc->createEntity();
    title->addComponent<PositionComponent>((width / 2) - (800 / 2), (height / 3) - (400 / 2));
    auto titleText = title->addComponent<TextComponent>("Settings",75);
    titleText->setColor(ColorCodes::COLOR_ORANGE);


    auto volumeTitle = sc->createEntity();
    volumeTitle->addComponent<PositionComponent>((width / 2) - 350, (height)  / 3);
    auto volumeTitleText = volumeTitle->addComponent<TextComponent>("Volume",65);
    volumeTitleText->setColor(ColorCodes::COLOR_ORANGE);

    auto gameVolume = sc->createEntity();
    auto volumeText = gameVolume->addComponent<TextComponent>(std::to_string((int)(lib->getVolume() * 100)),55);
    auto volumePos = gameVolume->addComponent<PositionComponent>(width - 580 , (height + 30)  / 3);
    volumeText->setColor(ColorCodes::COLOR_ORANGE);

    auto buttonVolumeUp = createButton(lib, sc,width - 500, height / 3,Textures::ARROW_RIGHT, volumeUp);
    buttonVolumeUp->addComponent<EntityLinkComponent>(gameVolume);

    auto buttonVolumeDown = createButton(lib, sc,width - 680, height / 3,Textures::ARROW_LEFT, volumeDown);
    buttonVolumeDown->addComponent<EntityLinkComponent>(gameVolume);

    auto howToPlay = sc->createEntity();
    howToPlay->addComponent<PositionComponent>((width / 2) - (400 / 2), (int) (height * 0.85) - (100 / 2));
    auto howToPlayText = howToPlay->addComponent<TextComponent>("How to play :",65);
    howToPlayText->setColor(ColorCodes::COLOR_ORANGE);

    createButton(lib, sc,(width / 2) - (400 / 2), (int) (height * 0.85) - (100 / 2),Textures::BACK_BUTTON, optionToMainMenu);
    return sc;
}