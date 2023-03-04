//
// Created by gugue on 03/03/2023.
//

#include "LobbyScene.h"
#include "TextComponent.h"
#include "PlayGameComponent.h"
#include "PlayGameSystem.h"

std::shared_ptr<Scene> lobbyScene(EnginePtr engine){
    auto sc = engine->createScene<Scene>();
    auto lib = engine->getModule<IGraphicLib>();
    auto height = lib->getWindow().getHeight();
    auto width = lib->getWindow().getWidth();

    auto background = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_1,-1);
    auto fourthground = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_2,-2);
    auto thirdground = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_3,-2);
    auto secondground = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_4,-3);
    auto firstground = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_5,-4);

    auto title = sc->createEntity();
    title->addComponent<PositionComponent>((width / 2) - 350, (height / 3) - (400 / 2));
    auto titleText = title->addComponent<TextComponent>("Waiting for players ...",75);
    titleText->setColor(ColorCodes::COLOR_ORANGE);

    auto instruction = sc->createEntity();
    instruction->addComponent<PositionComponent>((width / 2) - 350, (height / 2));
    auto instructionText = instruction->addComponent<TextComponent>("Press Space to start the game",50);
    instructionText->setColor(ColorCodes::COLOR_ORANGE);

    auto playGame = sc->createEntity();
    playGame->addComponent<PlayGameComponent>();

    sc->addSystem<PlayGameSystem>();
    sc->addSystem<VelocitySystem>();
    return sc;
}