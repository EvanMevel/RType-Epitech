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
#include "Client/ray/RaylibGraphicLib.h"
#include "DrawFixTextureSystem.h"
#include "Engine/Component/PositionComponent.h"
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
#include "MouseSystem.h"
#include "Engine/SceneHolder.h"
#include "SceneEnum.h"
#include "ScrollingTextureSystem.h"
#include "DrawSpriteSystem.h"
#include "SoundManager.h"
#include "Client/Consumers/ProjectileHitConsumer.h"
#include "Textures.h"
#include "Sprites.h"
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

    server->addSystem<StayAliveSystem>();

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
    auto music = lib->createMusic("assets/GameMusic.mp3");
    lib->playMusic(music);
    while (!window.shouldClose()) {
        auto it = lib->getExecs().begin();
        while (!window.shouldClose() && it != lib->getExecs().end()) {
            (*it)();
            it = lib->getExecs().erase(it);
        }
        if (window.shouldClose()) {
            break;
        }
        music->updateMusic();
        window.beginDrawing();
        window.setBackground(ColorCodes::COLOR_BLACK);
        lib->update(engine);
        window.endDrawing();
    }
    windowClosed = true;
}

void loadTextures(EnginePtr engine) {
    std::shared_ptr<IGraphicLib> lib = engine->getModule<IGraphicLib>();
    lib->registerTexture(Textures::TITLE, "assets/rtype.png");
    lib->registerTexture(Textures::PLAY_BUTTON, "assets/play-button.png");

    lib->registerTexture(Textures::BACKGROUND_1, "assets/Starry background  - Layer 01 - Solid colour.png");
    lib->registerTexture(Textures::BACKGROUND_2, "assets/Starry background  - Layer 02 - Shadows.png");
    lib->registerTexture(Textures::BACKGROUND_3, "assets/Starry background  - Layer 02 - Shadows 2.png");
    lib->registerTexture(Textures::BACKGROUND_4, "assets/Starry background  - Layer 03 - Stars.png");
    lib->registerTexture(Textures::BACKGROUND_5, "assets/Starry background  - Layer 03 - Stars 2.png");
}

void loadSounds(EnginePtr engine) {
    std::shared_ptr<IGraphicLib> lib = engine->getModule<IGraphicLib>();
    auto soundManager = engine->registerModule<SoundManager>();
    auto shootSound = lib->createSound("assets/basicShoot.ogg");

    soundManager->addSound(SoundType::PROJECTILE_SHOOT, shootSound);
    soundManager->addSound(SoundType::PROJECTILE_HIT,
                           lib->createSound("assets/projectile-hit.ogg"));
}

void loadSprites(EnginePtr engine) {
    std::shared_ptr<IGraphicLib> lib = engine->getModule<IGraphicLib>();
    const std::unique_ptr<Registry<Sprite>> &spriteRegistry = lib->getSprites();
    auto playerSpriteSheet = lib->createSpriteSheet("assets/r-typesheet42.gif");

    spriteRegistry->registerValue(Sprites::PLAYER_1,
                             playerSpriteSheet->createSprite(0, 3, 33, 14, 5, 0, 30, 4.0f));
    spriteRegistry->registerValue(Sprites::PLAYER_2,
                             playerSpriteSheet->createSprite(0, 20, 33, 14, 5, 0, 30, 4.0f));
    spriteRegistry->registerValue(Sprites::PLAYER_3,
                             playerSpriteSheet->createSprite(0, 37, 33, 14, 5, 0, 30, 4.0f));
    spriteRegistry->registerValue(Sprites::PLAYER_4,
                             playerSpriteSheet->createSprite(0, 54, 33, 14, 5, 0, 30, 4.0f));

    auto projSpriteSheet = lib->createSpriteSheet("assets/r-typesheet1.gif");

    auto projSprite = projSpriteSheet->createSprite(103, 170, 81, 16, 2, 0, 30);
    auto projSprite2 = projSpriteSheet->createSprite(267, 170, 81, 16, 2, 0, 30);
    spriteRegistry->registerValue(Sprites::PROJECTILE_1, projSprite);
    spriteRegistry->registerValue(Sprites::PROJECTILE_2, projSprite2);


    auto enemySpriteSheet = lib->createSpriteSheet("assets/r-typesheet23.gif");

    auto enemySprite = enemySpriteSheet->createSprite(0, 6, 33, 22, 8, 0, 30, 3.0f);
    spriteRegistry->registerValue(Sprites::ENEMY_1, enemySprite);

    auto enemySpriteSheet2 = lib->createSpriteSheet("assets/r-typesheet7.gif");
    auto enemySprite2 = enemySpriteSheet2->createSprite(1, 34, 33, 32, 3, 0, 30, 3.0f);

    spriteRegistry->registerValue(Sprites::ENEMY_2, enemySprite2);
}

void loadScenes(EnginePtr engine) {
    auto sceneHolder = engine->registerModule<SceneHolder>();
    auto sc = mainMenu(engine);
    engine->setScene(sc);
    sceneHolder->addScene(SceneEnum::MAIN_MENU,sc);
    sc->addSystem<VelocitySystem>();
}

void loadGraphsAndScenes(EnginePtr engine) {
    std::unique_lock<std::mutex> lck(graphicMutex);

    std::cout << "[Graphic] Starting..." << std::endl;

    std::shared_ptr<IGraphicLib> lib = engine->registerIModule<IGraphicLib, RaylibGraphicLib>();

    IWindow &window = lib->createWindow(1820, 1000, "R-type");
    window.setTargetFPS(60);
    lib->initAudio();
    //window.setFullScreen();
    std::cout << "[Graphic] Window created" << std::endl;
    loadTextures(engine);
    std::cout << "[Graphic] Textures ready" << std::endl;
    loadSprites(engine);
    std::cout << "[Graphic] Sprites ready" << std::endl;
    loadSounds(engine);
    std::cout << "[Graphic] Sounds ready" << std::endl;
    loadScenes(engine);
    std::cout << "[Graphic] Scenes ready" << std::endl;


    lib->addSystem<ScrollingTextureSystem>();
    lib->addSystem<DrawFixTextureSystem>();
    lib->addSystem<DrawSpriteSystem>();
    lib->addSystem<AnimationSystem>();
    lib->addSystem<MouseSystem>();


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