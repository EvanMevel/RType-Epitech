//
// Created by evans on 20/01/2023.
//

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
private:
    int m_socket;
#ifdef _WIN32
    WSADATA m_wsaData;
#endif
};


#endif //R_TYPE_SERVER_CROSSPLATFORMSOCKET_H
