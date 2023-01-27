//
// Created by evans on 26/01/2023.
//

#ifndef R_TYPE_SERVER_PACKETCONSUMEREXCEPTION_H
#define R_TYPE_SERVER_PACKETCONSUMEREXCEPTION_H

#include <exception>
#include <string>

class PacketConsumerException : public std::exception {
private:
    const std::string _message;
public:
    explicit PacketConsumerException(const std::string &message) : _message(message) {}

    const char *what() const noexcept override {
        return _message.c_str();
    }
};

#endif //R_TYPE_SERVER_PACKETCONSUMEREXCEPTION_H
