//
// Created by evans on 20/01/2023.
//

#include "CrossPlatformSocket.h"

CrossPlatformSocket::CrossPlatformSocket()
{
    m_socket = -1;
#ifdef _WIN32
    memset(&m_wsaData, 0, sizeof(m_wsaData));
#endif
}

CrossPlatformSocket::~CrossPlatformSocket()
{
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
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

#ifdef _WIN32
    addr.sin_addr.S_un.S_addr = inet_addr(address.c_str());
#else
    inet_aton(address, &addr.sin_addr);
#endif

    int sent_len = sendto(m_socket, message, len, 0, (struct sockaddr*)&addr, sizeof(addr));

    if (sent_len < 0) {
        return false;
    }

    return true;
}

bool CrossPlatformSocket::recvFrom(char* buffer, int len, std::string& address, unsigned short& port)
{
    struct sockaddr_in addr;
    int addrLen = sizeof(addr);
    memset(&addr, 0, sizeof(addr));

    int recv_len = recvfrom(m_socket, buffer, len, 0, (struct sockaddr*)&addr, &addrLen);

    if (recv_len < 0) {
        return recv_len;
    }
#ifdef _WIN32
    address = inet_ntoa(addr.sin_addr);
#else
    inet_ntop(AF_INET, &addr.sin_addr, address, INET_ADDRSTRLEN);
#endif
    port = ntohs(addr.sin_port);

    return recv_len;
}