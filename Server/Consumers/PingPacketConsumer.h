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

#ifndef R_TYPE_SERVER_PINGPACKETCONSUMER_H
#define R_TYPE_SERVER_PINGPACKETCONSUMER_H

#include "Server/RTypeServer.h"
#include "Engine/Network/Packets/PingPacket.h"

/**
 * @brief A consumer for the PingPacket
 */
class PingPacketConsumer : public PacketClientConsumer<PingPacket, std::shared_ptr<ClientData>> {
public:
    PingPacketConsumer();

    void consume(PingPacket &packet, std::shared_ptr<NetClient> client, std::shared_ptr<ClientData> data) override;
};


#endif //R_TYPE_SERVER_PINGPACKETCONSUMER_H
