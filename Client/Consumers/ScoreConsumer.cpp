//
// Created by aaama on 05/03/2023.
//

#include "ScoreConsumer.h"
#include "Client/Player/Player.h"
#include "Client/ScoreComponent.h"
#include "Client/TextComponent.h"

void changeScore(std::shared_ptr<IGraphicLib> lib,ScorePacket &packet, std::shared_ptr<Entity> entity) {
    auto textComponent = entity->getComponent<TextComponent>();
    auto scoreComponent = entity->getComponent<ScoreComponent>();
    if (scoreComponent != nullptr && textComponent != nullptr) {
        auto score = std::to_string(std::stoi(textComponent->getText()) + packet.getAddedScore());
        textComponent->setText(score);
    }
}

void ScoreConsumer::consume(ScorePacket &packet, std::unique_ptr<Engine> &engine, RTypeServer server) {
    auto player = engine->getModule<Player>();
    if (player) {
        if (player->entity->getId() != packet.getEntityId()) {
            return;
        }
        auto lib = engine->getModule<IGraphicLib>();
        std::function<void(std::shared_ptr<Entity>)> f = [&lib, &packet](std::shared_ptr<Entity> entity) {
            changeScore(lib, packet, entity);
        };
        engine->getScene()->forEachEntity(f);
    }
}
