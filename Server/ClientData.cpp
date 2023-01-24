//
// Created by evans on 24/01/2023.
//

#include "ClientData.h"
#include "Engine/TimeUtil.h"

long long int ClientData::getLastPing() const {
    return lastPing;
}

void ClientData::setLastPing(long long int lastPing) {
    ClientData::lastPing = lastPing;
}

ClientData::ClientData() : lastPing(getCurrentTime()) {

}
