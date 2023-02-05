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

#ifndef R_TYPE_SERVER_PACKETSENDINGSCENE_H
#define R_TYPE_SERVER_PACKETSENDINGSCENE_H


#include "Engine/Scene.h"
#include "RTypeServer.h"

/**
 * @brief Scene that sends packets to the clients when entities are removed
 */
class PacketSendingScene : public Scene {
private:
    RTypeServerPtr server;
public:
    PacketSendingScene(EntityManager &entityManager, const RTypeServerPtr &server);

    void removeEntity(std::shared_ptr<Entity> entity) override;

    void removeEntity(size_t entityId) override;

    void filterEntities(std::function<bool(std::shared_ptr<Entity>)> filter) override;

    void filterEntities(std::function<bool(std::shared_ptr<Entity>, EnginePtr)> func,
                        std::unique_ptr<Engine> &engine) override;
};


#endif //R_TYPE_SERVER_PACKETSENDINGSCENE_H
