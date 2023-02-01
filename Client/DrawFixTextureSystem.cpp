//
// Created by evans on 20/01/2023.
//

#include <iostream>
#include "DrawFixTextureSystem.h"
#include "Engine/Engine.h"
#include "FixTextureComponent.h"
#include "Engine/Component/PositionComponent.h"

void DrawFixTextureSystem::update(EnginePtr engine) {
    auto lib = engine->getModule<IGraphicLib>();
    if (lib == nullptr)
        return;
    if(engine->getScene() == nullptr)
        return;
    for (auto &entity: engine->getScene()->getEntities()) {
        auto textureComponent = entity->getComponent<FixTextureComponent>();
        auto posComponent = entity->getComponent<PositionComponent>();
        if (textureComponent != nullptr && posComponent != nullptr) {
            lib->drawTexture(textureComponent->getTexture(), posComponent->getX(), posComponent->getY(), ColorCodes::COLOR_WHITE);
        }
    }
}

std::string DrawFixTextureSystem::getName() {
    return "DrawFixTextureSystem";
}
