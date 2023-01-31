//
// Created by evans on 24/01/2023.
//

#include "RTypeServer.h"
#include "Engine/Network/Packets/HandshakeResponsePacket.h"

RTypeServer::RTypeServer(const std::string &address, unsigned short port) : NetServer(address, port) {

}

RTypeServer::~RTypeServer() {

}

bool RTypeServer::clientConnected(std::shared_ptr<NetClient> &client, std::shared_ptr<ClientData> data) {
    if (clients.size() >= MAX_CLIENTS) {
        std::cout << client->addressPort() << " kicked. Cause: too many clients already connected" << std::endl;
        client->sendPacket(HandshakeResponsePacket(HandshakeResponsePacketType::FULL, 0, 0));
        return false;
    }
    std::cout << "Client " << client->addressPort() << " connected" << std::endl;
    return true;
}

std::shared_ptr<ClientData> RTypeServer::createData(std::shared_ptr<NetClient> &client) {
    return std::make_shared<ClientData>();
}
