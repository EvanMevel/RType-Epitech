// MIT License
//
// Copyright (c) 2023 Audrey Amar, Théo Guguen, Evan Mevel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
        for (auto &entity: engine->getScene()->getEntities()) {
            auto typeComponent = entity->getComponent<EntityTypeComponent>();
            auto hitboxfixComponent= entity->getComponent<HitboxFixComponent>();
            if (typeComponent != nullptr && typeComponent->getType() == EntityType::BUTTON && hitboxfixComponent != nullptr) {
                if (hitboxfixComponent->getHitbox().contains(testMousePos.x,testMousePos.y)) {
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
