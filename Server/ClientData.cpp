//
// Created by evans on 24/01/2023.
//

#include <iostream>
#include "ClientData.h"
#include "Engine/TimeUtil.h"
#include "Engine/Network/Packets/PacketConsumerException.h"

long long int ClientData::getLastPing() const {
    return lastPing;
}

void ClientData::setLastPing(long long int lastPing) {
    ClientData::lastPing = lastPing;
}

ClientData::ClientData() : lastPing(getCurrentTime()) {

}

void ClientData::hasShakeHands() {
    if (!handshake) {
        throw PacketConsumerException("Client has not shake hands");
    }
}
