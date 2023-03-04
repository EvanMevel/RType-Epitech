//
// Created by gugue on 04/03/2023.
//

#include "StartGameConsumer.h"
#include "Client/Scenes.h"
#include "Engine/SceneHolder.h"
#include "Client/Musics.h"

void StartGameConsumer::consume(StartGamePacket &packet, std::unique_ptr<Engine> &engine, RTypeServer server) {
    auto sceneHolder = engine->getModule<SceneHolder>();
    auto sc = sceneHolder->getValue(Scenes::GAME);
    engine->setScene(sc);
    playMusic(engine->getModule<IGraphicLib>(),Musics::GAME_MUSIC);
}
