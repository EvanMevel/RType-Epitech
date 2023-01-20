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
private:
    CrossPlatformSocket socket;
    std::string address;
    unsigned short port;
    bool (*listener)(NetworkClient&, char*, int);
public:
    NetworkClient(const CrossPlatformSocket &socket, const std::string &address, unsigned short port);

    void send(const char *message, int length);

    void setListener(bool (*listener)(NetworkClient &, char *, int));

    bool messageReceived(std::string address, int port, char *message, int length) override;

    CrossPlatformSocket &getSocket() override;
};


#endif //R_TYPE_SERVER_NETWORKCLIENT_H
