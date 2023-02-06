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

#ifndef R_TYPE_SERVER_ENTITYINFOPACKET_H
#define R_TYPE_SERVER_ENTITYINFOPACKET_H


#include "IPacket.h"
#include "Engine/Entity.h"
#include "Engine/EntityType.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "Engine/Component/PositionComponent.h"

/**
 * @brief Packet sent to the client to inform him of the creation of an entity
 */
class EntityInfoPacket : public IPacket {
public:
    static const int ID = 7;
    EntityId id;
    EntityType type;
    int x;
    int y;
    int entityInfo = 0;

    EntityInfoPacket();

    explicit EntityInfoPacket(EntityPtr entity);

    EntityInfoPacket(EntityPtr entity, std::shared_ptr<EntityTypeComponent> type, std::shared_ptr<PositionComponent> pos);

    void write(ByteArray &buffer) const override;

    void read(ByteArray &buffer) override;
};


#endif //R_TYPE_SERVER_ENTITYINFOPACKET_H
