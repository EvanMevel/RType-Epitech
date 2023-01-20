//
// Created by evans on 20/01/2023.
//

#ifndef R_TYPE_SERVER_NETWORKSERVER_H
#define R_TYPE_SERVER_NETWORKSERVER_H

#include <thread>
#include "CrossPlatformSocket.h"
#include "NetworkClient.h"


class NetworkServer : public NetworkListener {
private:
    CrossPlatformSocket socket;
    std::thread listeningThread;
    std::vector<NetworkClient> _clients;
public:
    NetworkServer(const std::string &address, unsigned short port);
    virtual bool clientConnected(NetworkClient &client) = 0;
    virtual ~NetworkServer();

    bool messageReceived(std::string address, int port, char *message, int length) override;

    CrossPlatformSocket &getSocket() override;
};


#endif //R_TYPE_SERVER_NETWORKSERVER_H
