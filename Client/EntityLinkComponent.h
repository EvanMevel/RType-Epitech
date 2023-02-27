//
// Created by aaama on 27/02/2023.
//

#ifndef R_TYPE_CLIENT_ENTITYLINKCOMPONENT_H
#define R_TYPE_CLIENT_ENTITYLINKCOMPONENT_H


#include "Engine/Entity.h"

class EntityLinkComponent : public IComponent {
public:
    std::shared_ptr<Entity> entity;

    EntityLinkComponent();

    explicit EntityLinkComponent(const std::shared_ptr<Entity> &entity);

    virtual ~EntityLinkComponent();
};

#endif //R_TYPE_CLIENT_ENTITYLINKCOMPONENT_H
