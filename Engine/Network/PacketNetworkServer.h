//
// Created by evans on 21/01/2023.
//

#ifndef R_TYPE_SERVER_PACKETNETWORKSERVER_H
#define R_TYPE_SERVER_PACKETNETWORKSERVER_H

#include "NetworkServer.h"
#include "Engine/Network/Packets/PacketConsumers.h"
#include "Engine/Network/Packets/PacketSerializer.h"
#include "PacketReceiver.h"

class PacketNetworkClient : public NetworkClient, public PacketReceiver {
private:
    const unsigned char _magic = 242;
    PacketConsumers packetConsumers;
    PacketSerializer packetSerializer;
public:
    PacketNetworkClient(const CrossPlatformSocket &socket, const std::string &address, unsigned short port);

    PacketNetworkClient(const PacketNetworkClient &other) : NetworkClient(other), packetConsumers(other.packetConsumers),
                                                            packetSerializer(other.packetSerializer) {}

    ~PacketNetworkClient() override;

    bool messageReceived(std::string address, int port, char *message, int length) override;

    PacketConsumers &getConsumers();

    void send(const char *message, int length) override;
};

class PacketNetworkServer : public NetworkServer<PacketNetworkClient> {
public:
    PacketNetworkServer(const std::string &address, unsigned short port);
};


#endif //R_TYPE_SERVER_PACKETNETWORKSERVER_H
