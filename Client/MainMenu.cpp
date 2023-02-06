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

#include "MainMenu.h"
#include "Engine/Component/HitboxComponent.h"

std::shared_ptr<Scene> mainMenu(EnginePtr engine)
{
    auto sc = engine->createScene<Scene>();
    auto graph = engine->getModule<IGraphicLib>();

    auto background = createScrollingTextureComponent(graph, sc, "assets/Starry background  - Layer 01 - Solid colour.png",-1);
    auto fourthground = createScrollingTextureComponent(graph, sc, "assets/Starry background  - Layer 02 - Shadows.png",-2);
    auto thirdground = createScrollingTextureComponent(graph, sc, "assets/Starry background  - Layer 02 - Shadows 2.png",-2);
    auto secondground = createScrollingTextureComponent(graph, sc, "assets/Starry background  - Layer 03 - Stars.png",-3);
    auto firstground = createScrollingTextureComponent(graph, sc, "assets/Starry background  - Layer 03 - Stars 2.png",-4);

    auto height = graph->getWindow().getHeight();
    auto width = graph->getWindow().getWidth();

    auto title = createButton(engine,sc,"assets/rtype.png",width/2-(800/2),height/3-(400/2));
    auto playButton = createButton(engine,sc,"assets/play-button.png",width/2-(400/2),height*0.45-(100/2));
    auto hitboxPlaybutton = playButton->addComponent<HitboxComponent>();
    //auto optionButton = createButton(engine,sc,"assets/img_3.png",width/2-(400/2),height*0.65-(100/2));
    //auto quitButton = createButton(engine,sc,"img.png",width/2-(400/2),height*0.85-(100/2));

    return sc;
}