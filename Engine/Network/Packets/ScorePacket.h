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

//
// Created by gugue on 05/03/2023.
//

#ifndef PONG_SCOREPACKET_H
#define PONG_SCOREPACKET_H


#include "IPacket.h"

class ScorePacket: public IPacket {
private:
    EntityId entityId;
    int addedScore;
public:
    static const int ID = 47;

    void setEntityId(EntityId entityId);

    void setAddedScore(int addedScore);

    EntityId getEntityId() const;

    int getAddedScore() const;

    ScorePacket();

    ScorePacket(EntityId entityId, int addedScore);

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //PONG_SCOREPACKET_H
