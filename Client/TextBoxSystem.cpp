//
// Created by aaama on 21/02/2023.
//

#include "TextBoxSystem.h"
#include "Engine/Graphic/IGraphicLib.h"
#include "Engine/Component/PositionComponent.h"
#include "TextBoxComponent.h"

void drawTextBox(std::shared_ptr<IGraphicLib> lib, std::shared_ptr<Entity> entity) {
    auto textBoxComponent = entity->getComponent<TextBoxComponent>();
    if (textBoxComponent != nullptr) {
        auto rect = textBoxComponent->getRectangle();
        lib->drawRectangle(rect.x,rect.y, rect.width, rect.height, ColorCodes::COLOR_WHITE);
    }
}

void TextBoxSystem::update(std::unique_ptr<Engine> &engine) {

    auto lib = engine->getModule<IGraphicLib>();
    if (lib == nullptr)
        return;

    std::function<void(std::shared_ptr<Entity>)> draw = [&lib](std::shared_ptr<Entity> entity) {
        drawTextBox(lib, entity);
    };
    engine->getScene()->forEachEntity(draw);
}
