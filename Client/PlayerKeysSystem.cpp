//
// Created by evans on 28/01/2023.
//

#include "PlayerKeysSystem.h"

void PlayerKeysSystem::update(EnginePtr engine) {
    auto lib = engine->getModule<IGraphicLib>();
    player->up = lib->isKeyDown(KeyCodes::KEY_UP);
    player->down = lib->isKeyDown(KeyCodes::KEY_DOWN);
    player->left = lib->isKeyDown(KeyCodes::KEY_LEFT);
    player->right = lib->isKeyDown(KeyCodes::KEY_RIGHT);
    player->shoot = lib->isKeyDown(KeyCodes::KEY_SPACE);
}

PlayerKeysSystem::PlayerKeysSystem(const std::shared_ptr<Player> &player) : player(player) {}

std::string PlayerKeysSystem::getName() {
    return "PlayerKeysSystem";
}
