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
#include "Engine/SystemHolder.h"

/**
 * @brief NetworkRemoteServer is a class that represents a remote server.
 * @details It is used to send and receive packets to and from a remote server.
 * @details It is also used to listen to incoming packets from the remote server.
 */
template<class Data>
class NetworkRemoteServer : public NetworkListener, public PacketReceiver, public PacketSender<Data>, public SystemHolder {
private:
    Data data;
    CrossPlatformSocket socket;
    std::string _address;
    unsigned short _port;
public:
    NetworkRemoteServer(Data dat, const std::string &address, unsigned short port);

    NetworkRemoteServer(const NetworkRemoteServer &other) : data(other.data), socket(other.socket), _address(other._address), _port(other._port) {}

    void send(const char *message, int length) override;

    bool messageReceived(std::string address, int port, char *message, int length) override;

    void errorReceived(std::string address, int port, int err) override;

    CrossPlatformSocket &getSocket() override;
};

class Engine;

template class NetworkRemoteServer<Engine&>;

#endif //R_TYPE_SERVER_NETWORKREMOTESERVER_H
