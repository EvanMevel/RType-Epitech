//
// Created by evans on 28/01/2023.
//

#include "PlayerKeysSystem.h"

void PlayerKeysSystem::update(Engine &engine) {
    player->up = engine.getGraphicLib()->isKeyDown(KeyCodes::KEY_UP);
    player->down = engine.getGraphicLib()->isKeyDown(KeyCodes::KEY_DOWN);
    player->left = engine.getGraphicLib()->isKeyDown(KeyCodes::KEY_LEFT);
    player->right = engine.getGraphicLib()->isKeyDown(KeyCodes::KEY_RIGHT);
}

PlayerKeysSystem::PlayerKeysSystem(const std::shared_ptr<Player> &player) : player(player) {}

std::string PlayerKeysSystem::getName() {
    return "PlayerKeysSystem";
}
