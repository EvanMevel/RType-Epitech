// MIT License
//
// Copyright (c) 2023 Audrey Amar, Théo Guguen, Evan Mevel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef R_TYPE_SERVER_NETWORKLISTENER_H
#define R_TYPE_SERVER_NETWORKLISTENER_H

#include <memory>
#include <atomic>
#include <thread>
#include "CrossPlatformSocket.h"

/**
 * @brief NetworkListener is a class that listen to a socket
 * @details Override the messageReceived method to handle the received data
 */
class NetworkListener {
private:
    std::unique_ptr<std::thread> listeningThread;
    std::atomic<bool> running = false;

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

    bool isRunning() const;

};


#endif //R_TYPE_SERVER_NETWORKLISTENER_H
