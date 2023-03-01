//
// Created by aaama on 27/02/2023.
//

#include "OptionScene.h"


static void volumeUp(EnginePtr engine, std::shared_ptr<Entity> entity) {
    auto lib = engine->getModule<IGraphicLib>();
    lib->setVolume(lib->getVolume() + 0.01);
    lib->setVolumeMusic(lib->getMusic(),lib->getVolume());
}

static void volumeDown(EnginePtr engine, std::shared_ptr<Entity> entity) {
    auto lib = engine->getModule<IGraphicLib>();
    lib->setVolume(lib->getVolume() - 0.01);
    lib->setVolumeMusic(lib->getMusic(),lib->getVolume());
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

    auto background = createFixTexture(sc,Textures::BACKGROUND_1,0,0);
    auto firstground = createFixTexture(sc,Textures::BACKGROUND_2,0,0);
    auto secondground = createFixTexture(sc,Textures::BACKGROUND_4,0,0);


//faire un rectangle de fond    lib->drawRectangle(200, 200, width - 300, height-400,ColorCodes::COLOR_BLACK);

    auto gameVolume = sc->createEntity();

    createButton(lib, sc,width - 500, height / 3,Textures::ARROW_RIGHT, volumeUp);
    createButton(lib, sc,width - 680, height / 3,Textures::ARROW_LEFT, volumeDown);
    /*option :
        - son
        - langue ? (suedois ?)
        - key binding
     */
    createButton(lib, sc,(width / 2) - (400 / 2), (int) (height * 0.85) - (100 / 2),Textures::BACK_BUTTON, optionToMainMenu);
    return sc;
}