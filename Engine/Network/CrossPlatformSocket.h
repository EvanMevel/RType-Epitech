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

#ifndef R_TYPE_SERVER_CROSSPLATFORMSOCKET_H
#define R_TYPE_SERVER_CROSSPLATFORMSOCKET_H


#include <string>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>

#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#endif

/**
 * @brief Cross platform UDP socket for Linux and Windows
 */
class CrossPlatformSocket
{
public:
    CrossPlatformSocket();
    ~CrossPlatformSocket();

    bool create();
    bool bind(const std::string& address, unsigned short port);
    bool sendTo(const char* message, int len, const std::string& address, unsigned short port);
    int recvFrom(char* message, int len, std::string& address, unsigned short& port);

    std::string lastAddress;
    unsigned short lastPort;

    bool isClosed() const;

    int getSocket() const;

private:
    bool closed = false;
    int m_socket;
#ifdef _WIN32
    WSADATA m_wsaData;
#endif
};


#endif //R_TYPE_SERVER_CROSSPLATFORMSOCKET_H
