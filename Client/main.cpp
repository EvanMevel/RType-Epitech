//
// Created by aaama on 17/01/2023.
//

#include <iostream>
#include "ClientNetServer.h"
#include "Client/ray/RaylibGraphicLib.h"
#include "DrawFixTextureSystem.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Network/Packets/TestPacket.h"
#include "Engine/Network/Packets/EntityVelocityPacket.h"
#include "Client/Consumers/PingPacketConsumer.h"
#include "StayAliveSystem.h"
#include "Engine/Network/Packets/HandshakePacket.h"
#include "Client/Consumers/HandshakeResponseConsumer.h"
#include "Consumers/PlayerInfoConsumer.h"
#include "MainMenu.h"
#include "Engine/VelocitySystem.h"
#include "Engine/TickUtil.h"
#include "Client/Consumers/EntityInfoConsumer.h"
#include "Client/Consumers/EntityDestroyConsumer.h"
#include "Client/Consumers/EntityVelocityPacketConsumer.h"
#include "AnimationSystem.h"
#include <mutex>
#include <condition_variable>

std::mutex graphicMutex;
std::condition_variable cv;
bool graphicReady = false;

std::condition_variable cv2;
bool registeredConsumers = false;

bool windowClosed = false;

void execOnGraph(std::shared_ptr<IGraphicLib> lib, RTypeServer server) {
    std::cout << "Registering server consumer on graphic thread..." << std::endl;
    auto playerTexture = lib->createTexture("../Client/assets/player.png");
    server->addConsumer<PlayerInfoConsumer>(playerTexture);

    auto enemyTexture = lib->createTexture("../Client/assets/enemy.png");
    std::unordered_map<EntityType, std::shared_ptr<ITexture>> textures;
    textures[EntityType::PLAYER] = playerTexture;
    textures[EntityType::ENEMY] = enemyTexture;
    textures[EntityType::PROJECTILE] = lib->createTexture("../Client/assets/projectile.png");

    server->addConsumer<EntityInfoConsumer>(textures);

    registeredConsumers = true;
    cv2.notify_all();
}

void loadNetwork(EnginePtr engine) {
    std::unique_lock<std::mutex> lck(graphicMutex);

    std::cout << "[NETWORK] waiting for graphic" << std::endl;
    while (!graphicReady) {
        cv.wait(lck);
    }
    std::cout << "[NETWORK] graphic ready" << std::endl;
    RTypeServer server = engine->registerModule<ClientNetServer>(engine, "127.0.0.1", 4242);

    server->addConsumer<EntityVelocityPacketConsumer>();
    server->addConsumer<PingPacketConsumer>();
    server->addConsumer<HandshakeResponseConsumer>();
    server->addConsumer<EntityDestroyConsumer>();

    server->addSystem<StayAliveSystem>();

    std::function<void(std::shared_ptr<IGraphicLib>, RTypeServer server)> graphExec = execOnGraph;
    engine->getModule<IGraphicLib>()->execOnLibThread(graphExec, engine->getModule<IGraphicLib>(), server);

    std::cout << "Waiting for consumer register on graphicLib thread" << std::endl;

    while (!registeredConsumers) {
        cv2.wait(lck);
    }

    std::cout << "Sending handshake" << std::endl;
    server->startListening();
    server->sendPacket(HandshakePacket());

    auto ticker = engine->registerModule<TickUtil>(20);

    while (!windowClosed) {
        ticker->startTick();

        engine->updateScene(engine);
        server->update(engine);

        ticker->endTickAndWait();
    }

    std::cout << "Graphic closed, closing network" << std::endl;
}

void graphicLoop(EnginePtr engine) {
    auto lib = engine->getModule<IGraphicLib>();
    IWindow &window = lib->getWindow();

    while (!window.shouldClose()) {
        auto it = lib->getExecs().begin();
        while (it != lib->getExecs().end()) {
            (*it)();
            it = lib->getExecs().erase(it);
        }
        if (window.shouldClose()) {
            break;
        }
        window.beginDrawing();
        window.setBackground(ColorCodes::COLOR_BLACK);
        lib->update(engine);
        window.endDrawing();
    }
    windowClosed = true;
}

void loadScenes(EnginePtr engine) {
    auto sc = mainMenu(engine);
    engine->setScene(sc);

    sc->addSystem<VelocitySystem>();
}

void loadGraphsAndScenes(EnginePtr engine) {
    std::unique_lock<std::mutex> lck(graphicMutex);

    std::cout << "[Graphic] Starting..." << std::endl;

    std::shared_ptr<IGraphicLib> lib = engine->registerIModule<IGraphicLib, RaylibGraphicLib>();

    lib->addSystem<DrawFixTextureSystem>();
    lib->addSystem<AnimationSystem>();

    IWindow &window = lib->createWindow(1920, 1005, "teststs");
    window.setTargetFPS(60);
    std::cout << "[Graphic] Window created" << std::endl;

    loadScenes(engine);
    std::cout << "[Graphic] Scenes ready" << std::endl;

    graphicReady = true;
    cv.notify_all();

    std::cout << "[Graphic] Finished loading" << std::endl;

    lck.unlock();
}

void startGraph(EnginePtr engine) {
    loadGraphsAndScenes(engine);
    graphicLoop(engine);
}

void loadAll() {
    std::unique_ptr<Engine> engine = std::make_unique<Engine>();

    std::thread net(startGraph, std::ref(engine));

    loadNetwork(engine);

    net.join();
}

int main()
{
    loadAll();

    return 0;
}