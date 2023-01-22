//
// Created by evans on 20/01/2023.
//

#ifndef R_TYPE_SERVER_NETWORKSERVER_H
#define R_TYPE_SERVER_NETWORKSERVER_H

#include <thread>
#include "CrossPlatformSocket.h"
#include "NetworkClient.h"

template<class Client>
class NetworkServer : public NetworkListener {
private:
    CrossPlatformSocket socket;
    std::vector<Client> _clients;
public:
    NetworkServer(const std::string &address, unsigned short port);
    ~NetworkServer();

    virtual bool clientConnected(Client &client) = 0;

    bool messageReceived(std::string address, int port, char *message, int length) override;

    CrossPlatformSocket &getSocket() override;
};

class PacketNetworkClient;

template class NetworkServer<PacketNetworkClient>;


#endif //R_TYPE_SERVER_NETWORKSERVER_H
