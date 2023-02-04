//
// Created by aaama on 02/02/2023.
//

#include "MouseSystem.h"
#include "Engine/Engine.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "HitboxFixComponent.h"
#include "GameScene.h"
#include "Engine/SceneHolder.h"
#include "SceneEnum.h"
#include "Engine/Network/Packets/HandshakePacket.h"
#include "ClientNetServer.h"

void MouseSystem::update(EnginePtr engine) {
    auto lib = engine->getModule<IGraphicLib>();
    if (lib == nullptr)
        return;
    if(engine->getScene() == nullptr)
        return;
    if (lib->getMouse().isClicked(MouseCode::MOUSE_BUTTON_LEFT)){
        auto testMousePos = lib->getMouse().getPos();
        std::cout <<"pos x : " <<testMousePos.x << std::endl;
        std::cout <<"pos y : " <<testMousePos.y << std::endl;
        for (auto &entity: engine->getScene()->getEntities()) {
            auto typeComponent = entity->getComponent<EntityTypeComponent>();
            auto hitboxfixComponent= entity->getComponent<HitboxFixComponent>();
            if (typeComponent != nullptr && typeComponent->getType() == EntityType::BUTTON && hitboxfixComponent != nullptr) {
                if (hitboxfixComponent->getHitbox().contains(testMousePos.x,testMousePos.y)) {
                    std::cout <<"C Est DEDANS OU QUOI LA"<< std::endl;
                    auto sceneHolder = engine->registerModule<SceneHolder>();
                    auto sc = gameScene(engine);
                    engine->setScene(sc);
                    sceneHolder->addScene(SceneEnum::GAME,sc);
                    auto server = engine->getModule<ClientNetServer>();
                    std::cout << "Sending handshake" << std::endl;
                    server->startListening();
                    server->sendPacket(HandshakePacket());
                }
            }
        }
    }
}
