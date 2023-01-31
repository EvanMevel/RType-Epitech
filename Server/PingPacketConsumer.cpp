//
// Created by evans on 24/01/2023.
//

#include "PingPacketConsumer.h"
#include "Engine/TimeUtil.h"

PingPacketConsumer::PingPacketConsumer() {}

void PingPacketConsumer::consume(PingPacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) {
    data->hasShakeHands();

    //std::cout << "Ping received from " << client->addressPort() << " at " << packet.timestamp << std::endl;

    data->setLastPing(getCurrentTime());

    client->sendPacket(PingPacket::current());
}