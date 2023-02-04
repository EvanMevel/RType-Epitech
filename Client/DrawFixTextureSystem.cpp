//
// Created by evans on 20/01/2023.
//

#include <iostream>
#include "DrawFixTextureSystem.h"
#include "Engine/Engine.h"
#include "FixTextureComponent.h"
#include "Engine/Component/PositionComponent.h"

void drawEntity(std::shared_ptr<IGraphicLib> lib, std::shared_ptr<Entity> entity) {
    auto textureComponent = entity->getComponent<FixTextureComponent>();
    auto posComponent = entity->getComponent<PositionComponent>();
    if (textureComponent != nullptr && posComponent != nullptr) {
        lib->drawTexture(textureComponent->getTexture(), posComponent->getX(), posComponent->getY(), ColorCodes::COLOR_WHITE);
    }
}

void DrawFixTextureSystem::update(EnginePtr engine) {
    auto lib = engine->getModule<IGraphicLib>();
    if (lib == nullptr)
        return;
    if(engine->getScene() == nullptr)
        return;
    std::function<void(std::shared_ptr<Entity>)> draw = [&lib](std::shared_ptr<Entity> entity) {
        drawEntity(lib, entity);
    };
    engine->getScene()->forEachEntity(draw);
}

std::string DrawFixTextureSystem::getName() {
    return "DrawFixTextureSystem";
}
