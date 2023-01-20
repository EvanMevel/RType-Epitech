//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "Engine/Engine.h"
#include "Engine/Component/EntityTypeComponent.h"

class TestSystem : public ISystem {
    void update(Engine &engine) override {
        std::cout << "begin test system" << std::endl;
        for (auto &entity: engine.getScene()->getEntities()) {
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
    Engine e;
    Scene *sc = e.createScene();
    e.setScene(sc);
    Entity &ent = sc->createPlayer();
    Entity &ent2 = sc->createEntity();
    sc->addSystem(new TestSystem());
    sc->update(e);
    return 10;
}