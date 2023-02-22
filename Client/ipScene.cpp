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

#include "ipScene.h"
#include "Client/Textures/CreateButton.h"

static void changeIpButtonClick(EnginePtr engine) {
    auto sceneHolder = engine->getModule<SceneHolder>();
    auto sc = sceneHolder->getValue(Scenes::GAME);
    engine->setScene(sc);
    

    auto server = engine->getModule<ClientNetServer>();
    std::cout << "Sending handshake" << std::endl;
    server->startListening();
    server->sendPacket(HandshakePacket());
}

std::shared_ptr<Scene> ipScene(EnginePtr engine){
    auto sc = engine->createScene<Scene>();
    auto lib = engine->getModule<IGraphicLib>();
    auto height = lib->getWindow().getHeight();
    auto width = lib->getWindow().getWidth();

    auto background = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_1,-1);
    auto fourthground = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_2,-2);
    auto thirdground = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_3,-2);
    auto secondground = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_4,-3);
    auto firstground = createScrollingTextureComponent(lib, sc, Textures::BACKGROUND_5,-4);

    auto textBox = createTextBox(lib,sc,(lib->getWindow().getWidth() / 2) - (800 / 2), (int) (lib->getWindow().getHeight() * 0.45) - (100 / 2));

    createButton(lib, sc,(width / 2) - (400 / 2), (int) (height * 0.85) - (100 / 2),Textures::IP_BUTTON, changeIpButtonClick);
    sc->addSystem<VelocitySystem>();
    return sc;
}