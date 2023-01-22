//
// Created by evans on 21/01/2023.
//

#ifndef R_TYPE_SERVER_NETWORKREMOTESERVER_H
#define R_TYPE_SERVER_NETWORKREMOTESERVER_H


#include "CrossPlatformSocket.h"
#include "NetworkListener.h"
#include "PacketReceiver.h"
#include "PacketSender.h"
#include "Packets/PacketConsumers.h"

class NetworkRemoteServer : public NetworkListener, public PacketReceiver, public PacketSender {
private:
    CrossPlatformSocket socket;
    std::string _address;
    unsigned short _port;
public:
    NetworkRemoteServer(const std::string &address, unsigned short port);

    NetworkRemoteServer(const NetworkRemoteServer &other) : socket(other.socket), _address(other._address), _port(other._port) {}

    void send(const char *message, int length) override;

    bool messageReceived(std::string address, int port, char *message, int length) override;

    CrossPlatformSocket &getSocket() override;
};


#endif //R_TYPE_SERVER_NETWORKREMOTESERVER_H
