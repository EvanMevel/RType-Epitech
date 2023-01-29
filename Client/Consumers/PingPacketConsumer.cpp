//
// Created by evans on 24/01/2023.
//

#include <iostream>
#include "PingPacketConsumer.h"

void PingPacketConsumer::consume(PingPacket &packet, Engine &e) {
}

PingPacketConsumer::PingPacketConsumer(RTypeServer server) : ClientPacketConsumer(server) {}
