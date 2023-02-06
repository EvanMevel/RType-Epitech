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

#include <iostream>
#include "CrossPlatformSocket.h"

CrossPlatformSocket::CrossPlatformSocket() : lastAddress(), lastPort(0)
{
    m_socket = -1;
#ifdef _WIN32
    memset(&m_wsaData, 0, sizeof(m_wsaData));
#endif
}

CrossPlatformSocket::~CrossPlatformSocket()
{
    closed = true;
#ifdef _WIN32
    if (m_socket != -1) {
        closesocket(m_socket);
        WSACleanup();
    }
#else
    if (m_socket != -1) {
        close(m_socket);
    }
#endif
}

bool CrossPlatformSocket::create()
{
#ifdef _WIN32
    if (WSAStartup(MAKEWORD(2, 2), &m_wsaData) != 0) {
        return false;
    }
#endif

    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_socket <= 0) {
        return false;
    }

    return true;
}

bool CrossPlatformSocket::bind(const std::string& address, unsigned short port)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

#ifdef _WIN32
    addr.sin_addr.S_un.S_addr = inet_addr(address.c_str());
#else
    inet_aton(address.c_str(), &addr.sin_addr);
#endif

    if (::bind(m_socket, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        return false;
    }

    return true;
}

bool CrossPlatformSocket::sendTo(const char* message, int len, const std::string& address, unsigned short port)
{
    lastAddress = address;
    lastPort = port;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

#ifdef _WIN32
    addr.sin_addr.S_un.S_addr = inet_addr(address.c_str());
#else
    inet_aton(address.c_str(), &addr.sin_addr);
#endif

    int sent_len = sendto(m_socket, message, len, 0, (struct sockaddr*)&addr, sizeof(addr));

    if (sent_len < 0) {
        return false;
    }

    return true;
}

int CrossPlatformSocket::recvFrom(char* buffer, int len, std::string& address, unsigned short& port)
{
    struct sockaddr_in addr;
    unsigned int addrLen = sizeof(addr);
    memset(&addr, 0, sizeof(addr));

    int recv_len = recvfrom(m_socket, buffer, len, 0, (struct sockaddr*)&addr, &addrLen);


#ifdef _WIN32
    address = inet_ntoa(addr.sin_addr);
#else
    char *addressBuffer = new char[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET, &addr.sin_addr, addressBuffer, INET_ADDRSTRLEN);
    address = addressBuffer;
#endif
    port = ntohs(addr.sin_port);

    return recv_len;
}

bool CrossPlatformSocket::isClosed() const {
    return closed;
}
