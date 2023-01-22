//
// Created by evans on 21/01/2023.
//

#ifndef R_TYPE_SERVER_PACKETCONSUMERS_H
#define R_TYPE_SERVER_PACKETCONSUMERS_H


#include <any>
#include <unordered_map>
#include <memory>
#include "PacketConsumer.h"


template<class... ConsumeArgs>
class PacketConsumers {
private:
    std::unordered_map<int, std::shared_ptr<IPacketConsumer<ConsumeArgs...>>> _consumers;
public:
    PacketConsumers() = default;
    ~PacketConsumers() = default;

    template<class Consumer, typename... Args>
    void addConsumer(Args&&... args) {
        auto consumer = std::make_shared<Consumer>(args...);
        _consumers.emplace(consumer->getId(), consumer);
    }

    void consume(ByteArray &buffer, ConsumeArgs... args) {
        int id;
        buffer.read(id);
        auto consumer = _consumers.find(id);
        if (consumer != _consumers.end()) {
            consumer->second->consumePacket(buffer, args...);
        }
    }
};


#endif //R_TYPE_SERVER_PACKETCONSUMERS_H
