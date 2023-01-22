//
// Created by evans on 20/01/2023.
//

#ifndef R_TYPE_SERVER_NETWORKCLIENT_H
#define R_TYPE_SERVER_NETWORKCLIENT_H

#include <string>
#include <thread>
#include "CrossPlatformSocket.h"
#include "NetworkListener.h"

class NetworkClient : public NetworkListener {
protected:
    CrossPlatformSocket socket;
    std::string address;
    unsigned short port;
public:
    NetworkClient(const CrossPlatformSocket &socket, const std::string &address, unsigned short port);

    NetworkClient(const NetworkClient &other) : socket(other.socket), address(other.address), port(other.port) {}

    void send(const char *message, int length);

    CrossPlatformSocket &getSocket() override;
};


#endif //R_TYPE_SERVER_NETWORKCLIENT_H
