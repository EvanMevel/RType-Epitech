//
// Created by aaama on 28/02/2023.
//

#include "createFixTexture.h"

std::shared_ptr<Entity> createFixTexture( const std::shared_ptr<Scene> &sc, Textures texture, int posx,int posy){

    auto fixTextureEntity = sc->createEntity();
    auto textureComponent = fixTextureEntity->addComponent<FixTextureComponent>();
    textureComponent->setTextureId(texture);
    fixTextureEntity->addComponent<PositionComponent>(posx, posy);

    return fixTextureEntity;
}
