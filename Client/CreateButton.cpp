//
// Created by aaama on 24/01/2023.
//

#include "CreateButton.h"

Entity &createButton(Engine &e, std::shared_ptr<Scene> sc, const std::string &texturePath, int x, int y)
{
    Entity &button = sc->createEntity();
    auto buttonTexture = e.getGraphicLib()->createTexture(texturePath);
    button.addComponent<EntityTypeComponent>()->setType(BUTTON);
    button.addComponent<FixTextureComponent>()->setTexture(buttonTexture);
    auto pos = button.addComponent<PositionComponent>();
    pos->setX(x);
    pos->setY(y);

    return button;
}
