//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Component/EntityTypeComponent.h"

class TestSystem : public ISystem {
    void update(Engine &engine) override {
        std::cout << "begin test system" << std::endl;
        for (auto &entity: engine.getScene().getEntities()) {
            std::cout << "entity: " << entity.getId() << std::endl;
            auto *type = entity.getComponent<EntityTypeComponent>();
            if (entity.hasComponent<EntityTypeComponent>()) {
                std::cout << "type: " << type->getType() << std::endl;
            }
        }
    }
};

int main()
{
    Scene sc;
    Engine e(sc);
    Entity &ent = sc.createPlayer(e);
    Entity &ent2 = sc.createEntity(e);
    sc.addSystem(new TestSystem());
    sc.update(e);
    return 10;
}