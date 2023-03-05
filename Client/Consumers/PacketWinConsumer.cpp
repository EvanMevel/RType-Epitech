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

#include "PacketWinConsumer.h"
#include "Engine/Component/PositionComponent.h"
#include "Client/TextComponent.h"
#include "Client/Textures/Textures.h"
#include "Client/MainMenu.h"

void PacketWinConsumer::consume(PacketWin &packet, EnginePtr engine, RTypeServer server) {
    auto lib = engine->getModule<IGraphicLib>();
    auto height = lib->getWindow().getHeight();
    auto width = lib->getWindow().getWidth();
    auto sc = engine->getScene();
    auto title = sc->createEntity();
    title->addComponent<PositionComponent>((width / 2) - 350, (height / 3) - (400 / 2));
    auto titleText = title->addComponent<TextComponent>("Level Complete !", 200);
    titleText->setColor(ColorCodes::COLOR_ORANGE);
    createButton(lib, sc,(width / 2) - (400 / 2), (int) (height * 0.85) - (100 / 2),Textures::QUIT_BUTTON, quitGame);
}

PacketWinConsumer::PacketWinConsumer() {}
