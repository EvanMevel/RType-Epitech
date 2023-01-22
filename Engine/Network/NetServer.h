//
// Created by evans on 22/01/2023.
//

#ifndef R_TYPE_SERVER_NETSERVER_H
#define R_TYPE_SERVER_NETSERVER_H

#include <thread>
#include <utility>
#include "CrossPlatformSocket.h"
#include "PacketReceiver.h"
#include "PacketSender.h"
#include "NetworkListener.h"

class NetClient : public PacketReceiver {
protected:
    std::shared_ptr<CrossPlatformSocket> socket;
    std::string address;
    unsigned short port;
public:
    NetClient(const std::shared_ptr<CrossPlatformSocket> &socket, const std::string &address, unsigned short port);

    NetClient(const NetClient &other);

    ~NetClient() override;

    void send(const char *message, int length) override;

    const std::string &getAddress() const;

    unsigned short getPort() const;
};

template<class Packet, class Data>
class PacketClientConsumer : public PacketConsumer<Packet, std::shared_ptr<NetClient>, Data> {

};

template<class Data>
class NetServer : public NetworkListener , public PacketSender<std::shared_ptr<NetClient>, Data> {
private:
    const std::string &_address;
    unsigned short _port;
    std::shared_ptr<CrossPlatformSocket> socket;
    std::unordered_map<std::string, std::pair<std::shared_ptr<NetClient>, Data>> clients;
public:
    NetServer(const std::string &address, unsigned short port);

    bool messageReceived(std::string address, int port, char *message, int length) override;

    CrossPlatformSocket &getSocket() override;

    virtual Data createData(std::shared_ptr<NetClient> &client) = 0;

    virtual void clientConnected(std::shared_ptr<NetClient> &client, Data& data) = 0;

    void clientMessage(std::shared_ptr<NetClient> &client, Data& data, char *message, int length);

    void errorReceived(std::string address, int port, int err) override;

    template<class Packet>
    void broadcast(const Packet &packet) {
        for (auto &client : clients) {
            client.second.first->sendPacket(packet);
        }
    }
};

template class NetServer<int>;

#endif //R_TYPE_SERVER_NETSERVER_H
