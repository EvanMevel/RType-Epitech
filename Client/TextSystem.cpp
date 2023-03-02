//
// Created by aaama on 02/03/2023.
//

#include "TextSystem.h"
#include "Engine/Graphic/IGraphicLib.h"
#include "TextComponent.h"
#include "Engine/Component/PositionComponent.h"

void drawText(std::shared_ptr<IGraphicLib> lib, std::shared_ptr<Entity> entity) {
    auto textComponent = entity->getComponent<TextComponent>();
    auto textPosComponent = entity->getComponent<PositionComponent>();
    if (textComponent != nullptr && textPosComponent != nullptr) {
        lib->drawText(textComponent->getText(), textPosComponent->getX(), textPosComponent->getY(), textComponent->getFontSize(), ColorCodes::COLOR_ORANGE);
    }
}

void TextSystem::update(EnginePtr engine) {
    auto lib = engine->getModule<IGraphicLib>();
    if (lib == nullptr)
        return;
    std::function<void(std::shared_ptr<Entity>)> draw = [&lib](std::shared_ptr<Entity> entity) {
        drawText(lib, entity);
    };
    engine->getScene()->forEachEntity(draw);
}
