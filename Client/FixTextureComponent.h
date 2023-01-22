//
// Created by evans on 20/01/2023.
//

#ifndef R_TYPE_SERVER_FIXTEXTURECOMPONENT_H
#define R_TYPE_SERVER_FIXTEXTURECOMPONENT_H

#include "Engine/Component/IComponent.h"
#include "Engine/Graphic/ITexture.h"

class FixTextureComponent : public IComponent {
private:
    ITexture texture;
public:
    explicit FixTextureComponent();

    ~FixTextureComponent() override = default;

    const ITexture &getTexture() const;

    void setTexture(const ITexture &texture);
};


#endif //R_TYPE_SERVER_FIXTEXTURECOMPONENT_H
