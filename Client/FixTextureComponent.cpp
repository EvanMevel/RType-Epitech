//
// Created by evans on 20/01/2023.
//

#include "FixTextureComponent.h"

const ITexture &FixTextureComponent::getTexture() const {
    return texture;
}

FixTextureComponent::FixTextureComponent() {

}

void FixTextureComponent::setTexture(const ITexture &texture) {
    FixTextureComponent::texture = texture;
}
