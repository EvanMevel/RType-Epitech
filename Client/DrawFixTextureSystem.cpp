//
// Created by evans on 20/01/2023.
//

#include "DrawFixTextureSystem.h"
#include "Engine/Engine.h"
#include "FixTextureComponent.h"
#include "Engine/Component/PositionComponent.h"

void DrawFixTextureSystem::update(Engine &engine) {
    if (engine.getGraphicLib() == nullptr)
        return;

    for (auto &entity: engine.getScene()->getEntities()) {
        auto textureComponent = entity.getComponent<FixTextureComponent>();
        auto posComponent = entity.getComponent<PositionComponent>();
        if (textureComponent != nullptr && posComponent != nullptr) {
            engine.getGraphicLib()->drawTexture(textureComponent->getTexture(), posComponent->getX(), posComponent->getY(), ColorCodes::COLOR_WHITE);
        }
    }
}
