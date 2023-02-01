//
// Created by evans on 20/01/2023.
//

#include "FixTextureComponent.h"

FixTextureComponent::FixTextureComponent() {

}

const std::shared_ptr<ITexture> &FixTextureComponent::getTexture() const {
    return texture;
}

void FixTextureComponent::setTexture(const std::shared_ptr<ITexture> &texture) {
    FixTextureComponent::texture = texture;
}
