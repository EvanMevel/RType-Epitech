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

#include "PlayerMoveConsumer.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"
#include "Engine/TickUtil.h"
#include "Engine/Component/PhysicComponent.h"

PlayerMoveConsumer::PlayerMoveConsumer(EnginePtr e) : RTypePlayerPacketConsumer(e) {}

void PlayerMoveConsumer::consume(PlayerMovePacket &packet, std::shared_ptr<NetClient> client,
                                 std::shared_ptr<ClientData> data, std::shared_ptr<Entity> player) {
    if (player == nullptr)
        return;
    auto physics = player->getOrCreate<PhysicComponent>();
    physics->acceleration = packet.acceleration;

    auto ticker = e->getModule<TickUtil>();

    EntityVelocityPacket velPacket(player, ticker->getCurrentTick());
    e->getModule<RTypeServer>()->broadcast(velPacket);
}
