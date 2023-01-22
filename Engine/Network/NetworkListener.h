//
// Created by evans on 20/01/2023.
//

#ifndef R_TYPE_SERVER_NETWORKLISTENER_H
#define R_TYPE_SERVER_NETWORKLISTENER_H


#include <thread>
#include "CrossPlatformSocket.h"

/**
 * @brief NetworkListener is a class that listen to a socket
 * @details Override the messageReceived method to handle the received data
 */
class NetworkListener {
private:
    std::thread listeningThread;

public:
    virtual ~NetworkListener();

    void startListening();
    void listen();
    /**
     * @brief Called when a message is received
     * @param address The address of the sender
     * @param port The port of the sender
     * @param buffer The buffer containing the data
     * @param size The size of the data
     */
    virtual bool messageReceived(std::string address, int port, char *message, int length) = 0;
    /**
     * @brief Called when an error is received
     * @param address The address of the sender
     * @param port The port of the sender
     * @param err The error code
     */
    virtual void errorReceived(std::string address, int port, int err) = 0;
    virtual CrossPlatformSocket &getSocket() = 0;

};


#endif //R_TYPE_SERVER_NETWORKLISTENER_H
