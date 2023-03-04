//
// Created by gugue on 04/03/2023.
//

#include "PlayGameSystem.h"
#include "PlayGameComponent.h"
#include "ClientNetServer.h"
#include "Engine/Network/Packets/StartGamePacket.h"

void playGame(std::shared_ptr<IGraphicLib> lib, std::shared_ptr<Entity> entity, EnginePtr engine) {
    auto playGameComponent = entity->getComponent<PlayGameComponent>();
    if (playGameComponent != nullptr) {
        if (lib->isKeyPressed(KeyCodes::KEY_SPACE)) {
            engine->getModule<ClientNetServer>()->sendPacket(StartGamePacket());
        }
    }
}

void PlayGameSystem::update(std::unique_ptr<Engine> &engine) {
    auto lib = engine->getModule<IGraphicLib>();
    if (lib == nullptr)
        return;
    if(engine->getScene() == nullptr)
        return;
    std::function<void(std::shared_ptr<Entity>)> play = [&lib, &engine](std::shared_ptr<Entity> entity) {
        playGame(lib, entity, engine);
    };
    engine->getScene()->forEachEntity(play);
}