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

#include "HandshakeConsumer.h"
#include "Engine/Network/Packets/HandshakeResponsePacket.h"
#include "Engine/EntityUtils.h"
#include "Engine/Network/Packets/PlayerInfoPacket.h"
#include "Engine/TickUtil.h"
#include "Engine/Network/Packets/EntityInfoPacket.h"
#include "Engine/Component/PlayerInfoComponent.h"
#include "Server/PlayerList.h"
#include "Engine/engineLua/LuaEntityTypeFactory.h"
#include "Engine/Component/WeaponComponent.h"
#include "Server/SynchronizedWeapon.h"

HandshakeConsumer::HandshakeConsumer(EnginePtr e) : RTypePacketConsumer(e) {}

static void sendEntitiesInfo(const std::shared_ptr<NetClient>& client, std::shared_ptr<Scene> scene) {
    std::function<void(std::shared_ptr<Entity>)> sendEntityInfo = [&client](std::shared_ptr<Entity> entity) {
        auto pos = entity->getComponent<PositionComponent>();
        auto type = entity->getComponent<EntityTypeComponent2>();
        if (pos && type) {
            EntityInfoPacket packet(entity, type, pos);
            client->sendPacket(packet);
        }
    };
    scene->forEachEntity(sendEntityInfo);
}

void HandshakeConsumer::consume(HandshakePacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) {
    auto server = e->getModule<RTypeServer>();
    std::cout << "Handshake received" << std::endl;
    data->handshake = true;

    // Send handshake response with tick information
    auto ticker = e->getModule<TickUtil>();
    unsigned long long startedMs = std::chrono::time_point_cast<std::chrono::milliseconds>(ticker->getStarted()).time_since_epoch().count();
    HandshakeResponsePacket responsePacket(HandshakeResponsePacketType::OK, ticker->getCurrentTick(), startedMs);
    client->sendPacket(responsePacket);


}
