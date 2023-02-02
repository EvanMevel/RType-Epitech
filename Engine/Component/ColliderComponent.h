//
// Created by evans on 02/02/2023.
//

#ifndef R_TYPE_SERVER_COLLIDERCOMPONENT_H
#define R_TYPE_SERVER_COLLIDERCOMPONENT_H

#include "Engine/Component/IComponent.h"
#include "Engine/Hitbox.h"
#include "Engine/Engine.h"

class ColliderComponent : public IComponent {
public:
    std::function<void(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other,
            std::unordered_map<size_t, std::vector<std::tuple<Hitbox, std::shared_ptr<Entity>>>> &teams)> _onCollision;


    void onCollision(EnginePtr engine, std::shared_ptr<Entity> self, std::shared_ptr<Entity> other,
                     std::unordered_map<size_t, std::vector<std::tuple<Hitbox, std::shared_ptr<Entity>>>> &teams);
};


#endif //R_TYPE_SERVER_COLLIDERCOMPONENT_H
