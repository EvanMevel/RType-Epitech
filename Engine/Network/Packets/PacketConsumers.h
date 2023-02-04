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

#ifndef R_TYPE_SERVER_PACKETCONSUMERS_H
#define R_TYPE_SERVER_PACKETCONSUMERS_H


#include <any>
#include <unordered_map>
#include <memory>
#include "PacketConsumer.h"

/**
 * @brief A class that hold packet consumers
 * @tparam ConsumeArgs The arguments that will be passed to the consumers
 */
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
