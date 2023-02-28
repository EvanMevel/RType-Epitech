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

#include <iostream>
#include "Pong/ray/RaylibGraphicLib.h"
#include "Pong/Scenes.h"
#include "Pong/Textures.h"
#include "Pong/Sounds.h"
#include "Engine/TickUtil.h"
#include <mutex>
#include <condition_variable>
#include "Pong/DrawFixTextureSystem.h"
#include "Pong/MouseSystem.h"
#include "PlayerKeys.h"
#include "PlayerKeysSystem.h"
#include "Pong.h"


bool windowClosed = false;

void loadGame(EnginePtr engine) {
    auto ticker = engine->registerModule<TickUtil>(ENGINE_TPS);

    while (!windowClosed) {
        ticker->startTick();

        engine->updateScene(engine);

        ticker->endTickAndWait();
    }

    std::cout << "Graphic closed, closing network" << std::endl;
}

void graphicLoop(EnginePtr engine) {
    auto lib = engine->getModule<IGraphicLib>();
    IWindow &window = lib->getWindow();
    auto music = lib->createMusic("GameMusic.mp3");
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

void loadGraphsAndScenes(EnginePtr engine) {
    std::cout << "[Graphic] Starting..." << std::endl;

    std::shared_ptr<IGraphicLib> lib = engine->registerIModule<IGraphicLib, RaylibGraphicLib>();

    IWindow &window = lib->createWindow(PONG_WINDOW_WIDTH, PONG_WINDOW_HEIGHT, "PONG");
    window.setTargetFPS(60);
    lib->initAudio();
    //window.setFullScreen();
    std::cout << "[Graphic] Window created" << std::endl;
    loadTextures(lib);
    std::cout << "[Graphic] Textures ready" << std::endl;
    loadSounds(lib);
    std::cout << "[Graphic] Sounds ready" << std::endl;
    loadScenes(engine);
    std::cout << "[Graphic] Scenes ready" << std::endl;


    lib->addSystem<DrawFixTextureSystem>();
    lib->addSystem<MouseSystem>();
    lib->addSystem<PlayerKeysSystem>();

    std::cout << "[Graphic] Finished loading" << std::endl;
}

void startGraph(EnginePtr engine) {
    loadGraphsAndScenes(engine);
    graphicLoop(engine);
}

void loadAll() {
    std::unique_ptr<Engine> engine = std::make_unique<Engine>();

    engine->registerModule<PlayerKeys>();

    std::thread graphThread(startGraph, std::ref(engine));

    loadGame(engine);

    graphThread.join();
}

int main()
{
    loadAll();

    return 0;
}