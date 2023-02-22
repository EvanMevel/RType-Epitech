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
        int key = lib->getCharPressed();
        while(key > 0) {
            textBoxComponent->setText(textBoxComponent->getText() + (char) key);
            key = lib->getCharPressed();
        }if (lib->isKeyPressed(KeyCodes::KEY_BACKSPACE) && !textBoxComponent->getText().empty()) {
            textBoxComponent->setText(textBoxComponent->getText().substr(0, textBoxComponent->getText().length() - 1));
        }
        std::cout<<textBoxComponent->getText()<<std::endl;
        lib->drawText(textBoxComponent->getText(),rect.x +5, rect.y,35,ColorCodes::COLOR_BLACK);
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
