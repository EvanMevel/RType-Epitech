/// MIT License
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

#include <iostream>
#include "ClientNetServer.h"
#include "Ray/ray/RaylibGraphicLib.h"
#include "Client/Scenes.h"
#include "Client/Textures/Textures.h"
#include "Engine/Graphic/Textures/DrawFixTextureSystem.h"
#include "Engine/Graphic/Textures/ScrollingTextureSystem.h"
#include "Engine/Graphic/Sprites/DrawSpriteSystem.h"
#include "Engine/Graphic/Textures/DrawTextureNameSystem.h"
#include "Client/Sounds.h"
#include "Client/Consumers/PlayerInfoConsumer.h"
#include "Client/Consumers/EntityInfoConsumer.h"
#include "Client/Consumers/EntityDestroyConsumer.h"
#include "Client/Consumers/EntityVelocityPacketConsumer.h"
#include "Client/Consumers/ProjectileHitConsumer.h"
#include "Client/Consumers/HandshakeResponseConsumer.h"
#include "Client/Consumers/PingPacketConsumer.h"
#include "AnimationSystem.h"
#include "MouseSystem.h"
#include "Engine/TickUtil.h"
#include "StayAliveSystem.h"
#include "Engine/engineLua/LuaLoader.h"
#include "TextBoxSystem.h"
#include "Client/Consumers/DamageConsumer.h"
#include "Client/Textures/CooldownSystem.h"
#include "Client/Textures/LifeSystem.h"
#include "Musics.h"
#include "TextSystem.h"
#include "PlayGameSystem.h"
#include "Client/Consumers/StartGameConsumer.h"
#include "Engine/BossCreator.h"
#include "BossCreatorClient.h"
#include "Client/Consumers/PacketWinConsumer.h"
#include "Client/Consumers/PacketSwitchWeaponConsumer.h"
#include <mutex>
#include <condition_variable>

std::mutex graphicMutex;
std::condition_variable cv;
bool graphicReady = false;

bool windowClosed = false;

void loadNetwork(EnginePtr engine) {
    std::unique_lock<std::mutex> lck(graphicMutex);

    std::cout << "[NETWORK] waiting for graphic" << std::endl;
    while (!graphicReady) {
        cv.wait(lck);
    }
    std::cout << "[NETWORK] graphic ready" << std::endl;

    char *rtypeServerIp = std::getenv("RTYPE_SERVER_IP");
    std::string serverIp = rtypeServerIp ? rtypeServerIp : "127.0.0.1";
    char *rtypeServerPort = std::getenv("RTYPE_SERVER_PORT");
    int serverport = rtypeServerPort ? std::stoi(rtypeServerPort) : 4242;

    RTypeServer server = engine->registerModule<ClientNetServer>(engine, serverIp, serverport);

    server->addConsumer<EntityVelocityPacketConsumer>();
    server->addConsumer<PingPacketConsumer>();
    server->addConsumer<HandshakeResponseConsumer>();
    server->addConsumer<EntityDestroyConsumer>();

    server->addConsumer<PlayerInfoConsumer>();

    server->addConsumer<EntityInfoConsumer>();

    server->addConsumer<ProjectileHitConsumer>();

    server->addConsumer<DamageConsumer>();

    server->addSystem<StayAliveSystem>();

    server->addConsumer<StartGameConsumer>();

    server->addConsumer<PacketWinConsumer>();

    server->addConsumer<PacketSwitchWeaponConsumer>();

    auto ticker = engine->registerModule<TickUtil>(ENGINE_TPS);

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
        while (!window.shouldClose() && it != lib->getExecs().end()) {
            (*it)();
            it = lib->getExecs().erase(it);
        }
        if (window.shouldClose()) {
            break;
        }
        lib->getMusic()->updateMusic();
        window.beginDrawing();
        window.setBackground(ColorCodes::COLOR_BLACK);
        lib->update(engine);
        window.endDrawing();
    }
    windowClosed = true;
}

void loadGraphsAndScenes(EnginePtr engine) {
    std::unique_lock<std::mutex> lck(graphicMutex);

    std::cout << "[Graphic] Starting..." << std::endl;

    char *rtypeAssetsPath = std::getenv("RTYPE_ASSETS_PATH");
    std::string assetsPath = rtypeAssetsPath ? rtypeAssetsPath : "assets/";
    std::shared_ptr<IGraphicLib> lib = engine->registerIModule<IGraphicLib, RaylibGraphicLib>(assetsPath);

    IWindow &window = lib->createWindow(1820, 1000, "R-type");
    window.setTargetFPS(60);
    lib->initAudio();
    //window.setFullScreen();
    std::cout << "[Graphic] Window created" << std::endl;
    loadTextures(lib);
    std::cout << "[Graphic] Textures ready" << std::endl;

    auto luaLoad = engine->getModule<LuaLoader>();
    luaLoad->loadEntitySprites(lib);
    luaLoad->loadTextures(lib);
    auto bossSpriteSheets = lib->createSpriteSheet("r-typesheet32rotate.gif");
    auto sprite = bossSpriteSheets->createSprite(0, 0, 143, 260, 4, 0, 30, 3.0);
    lib->getSpriteProperties()->registerValue("BOSS", sprite);

    std::cout << "[Graphic] Sprites ready" << std::endl;
    loadSounds(lib);
    std::cout << "[Graphic] Sounds ready" << std::endl;
    loadMusics(lib);
    std::cout << "[Graphic] Musics ready" << std::endl;
    loadScenes(engine);
    std::cout << "[Graphic] Scenes ready" << std::endl;

    lib->addSystem<ScrollingTextureSystem>();
    lib->addSystem<DrawFixTextureSystem>();
    lib->addSystem<DrawTextureNameSystem>();
    lib->addSystem<DrawSpriteSystem>();
    lib->addSystem<AnimationSystem>();
    lib->addSystem<MouseSystem>();
    lib->addSystem<TextBoxSystem>();
    lib->addSystem<LifeSystem>();
    lib->addSystem<CooldownSystem>();
    lib->addSystem<TextSystem>();
    lib->addSystem<PlayGameSystem>();

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

    auto luaLoad = engine->registerModule<LuaLoader>();
    auto typeFactory = engine->registerModule<LuaEntityTypeFactory>();
    auto levelFactory = engine->registerModule<LuaLevelFactory>();
    auto weaponFactory = engine->registerIModule<LuaWeaponFactoryBase, LuaWeaponFactory<Weapon>>();
    auto boss = engine->registerIModule<BossCreator,BossCreatorClient>();

    luaLoad->loadFolder("config");
    luaLoad->loadEntityTypes(typeFactory, weaponFactory);
    luaLoad->loadLevels(levelFactory);

    std::thread graphThread(startGraph, std::ref(engine));

    loadNetwork(engine);

    graphThread.join();
}

int main()
{
    loadAll();

    return 0;
}