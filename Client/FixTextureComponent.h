//
// Created by evans on 20/01/2023.
//

#ifndef R_TYPE_SERVER_FIXTEXTURECOMPONENT_H
#define R_TYPE_SERVER_FIXTEXTURECOMPONENT_H

#include <memory>
#include "Engine/Component/IComponent.h"
#include "Engine/Graphic/ITexture.h"

class FixTextureComponent : public IComponent {
private:
    std::shared_ptr<ITexture> texture;
public:
    explicit FixTextureComponent();

    ~FixTextureComponent() override = default;

    const std::shared_ptr<ITexture> &getTexture() const;

    void setTexture(const std::shared_ptr<ITexture> &texture);
};


#endif //R_TYPE_SERVER_FIXTEXTURECOMPONENT_H
