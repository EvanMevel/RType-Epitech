//
// Created by evans on 28/01/2023.
//

#include "PlayerKeysSystem.h"

void PlayerKeysSystem::update(Engine &engine) {
    auto lib = engine.getEngineComponent<IGraphicLib>();
    player->up = lib->isKeyDown(KeyCodes::KEY_UP);
    player->down = lib->isKeyDown(KeyCodes::KEY_DOWN);
    player->left = lib->isKeyDown(KeyCodes::KEY_LEFT);
    player->right = lib->isKeyDown(KeyCodes::KEY_RIGHT);
}

PlayerKeysSystem::PlayerKeysSystem(const std::shared_ptr<Player> &player) : player(player) {}

std::string PlayerKeysSystem::getName() {
    return "PlayerKeysSystem";
}
