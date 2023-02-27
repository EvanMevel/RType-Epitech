//
// Created by aaama on 21/02/2023.
//

#include "CreateTextBox.h"
#include "Client/TextBoxComponent.h"
#include "Engine/Component/PositionComponent.h"
#include "EntityLinkComponent.h"

std::shared_ptr<Entity> createTextBox(const std::shared_ptr<IGraphicLib> &lib, const std::shared_ptr<Scene> &sc, int x, int y){
    auto textbox = sc->createEntity();
    textbox->addComponent<TextBoxComponent>();
    auto textBoxcomponent = textbox->getComponent<TextBoxComponent>();
    auto rect = MyRectangle(x, y,800,100);
    textBoxcomponent->setRectangle(rect);
    return textbox;
}