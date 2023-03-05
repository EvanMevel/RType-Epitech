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

#ifndef R_TYPE_SERVER_PACKETCONSUMER_H
#define R_TYPE_SERVER_PACKETCONSUMER_H

#include "ByteArray.h"
#include "IPacketConsumer.h"

/**
 * @brief PacketConsumer is a consumer that will consume a ByteArray and will call the callback with the packe
 * @tparam Packet The packet that will be consumed
 * @tparam Args The arguments that will be passed to the callback
 */
template<class Packet, class... Args>
class PacketConsumer : public IPacketConsumer<Args...> {
public:
    void consumePacket(ByteArray &buffer, Args ...args) override {
        Packet packet;
        packet.read(buffer);
        this->consume(packet, args...);
    }
    int getId() override {
        return Packet::ID;
    }
    /**
     * @brief The callback that will be called when the packet is consumed
     * @param packet The packet that was consumed
     * @param args The arguments that were passed to the consumePacket method
     */
    virtual void consume(Packet &packet, Args ...args) = 0;
};


#endif //R_TYPE_SERVER_PACKETCONSUMER_H
