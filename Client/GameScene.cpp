//
// Created by aaama on 03/02/2023.
//

#include "GameScene.h"
#include "SceneEnum.h"
#include "Engine/SceneHolder.h"
#include "Engine/VelocitySystem.h"
#include "Client/Consumers/PlayerInfoConsumer.h"

std::shared_ptr<Scene> gameScene(EnginePtr engine){
    auto sc = engine->createScene<Scene>();
    auto background = sc->createEntity();
    auto lib = engine->getModule<IGraphicLib>();

    auto playerTexture = lib->createTexture("../Client/assets/player.png");
   // server->addConsumer<PlayerInfoConsumer>(playerTexture);

    auto enemyTexture = lib->createTexture("../Client/assets/enemy.png");
    std::unordered_map<EntityType, std::shared_ptr<ITexture>> textures;
    textures[EntityType::PLAYER] = playerTexture;
    textures[EntityType::ENEMY] = enemyTexture;
    textures[EntityType::PROJECTILE] = lib->createTexture("../Client/assets/projectile.png");

    return sc;
}