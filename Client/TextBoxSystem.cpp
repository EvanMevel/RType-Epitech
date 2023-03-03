// MIT License
//
// Copyright (c) 2023 Audrey Amar, Théo Guguen, Evan Mevel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
