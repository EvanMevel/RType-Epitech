//
// Created by aaama on 24/01/2023.
//

#include "CreateButton.h"

std::shared_ptr<Entity> createButton(EnginePtr engine, std::shared_ptr<Scene> sc, const std::string &texturePath, int x, int y)
{
    auto button = sc->createEntity();
    auto buttonTexture = engine->getModule<IGraphicLib>()->createTexture(texturePath);
    button->addComponent<EntityTypeComponent>()->setType(BUTTON);
    button->addComponent<FixTextureComponent>()->setTexture(buttonTexture);
    auto pos = button->addComponent<PositionComponent>();
    pos->setX(x);
    pos->setY(y);

    return button;
}
