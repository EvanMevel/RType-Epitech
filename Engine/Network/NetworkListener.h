//
// Created by evans on 20/01/2023.
//

#ifndef R_TYPE_SERVER_NETWORKLISTENER_H
#define R_TYPE_SERVER_NETWORKLISTENER_H


#include <thread>
#include "CrossPlatformSocket.h"

class NetworkListener {
private:
    std::thread listeningThread;

public:
    virtual ~NetworkListener();

    void startListening();
    void listen();
    virtual bool messageReceived(std::string address, int port, char *message, int length) = 0;
    virtual CrossPlatformSocket &getSocket() = 0;

};


#endif //R_TYPE_SERVER_NETWORKLISTENER_H
