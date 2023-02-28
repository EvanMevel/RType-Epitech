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
#include "Engine/SceneHolder.h"
#include "Scenes.h"
#include "Pong/FixTextureComponent.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Component/EntityTypeComponent2.h"
#include "Engine/Component/HitboxComponent.h"
#include "ButtonComponent.h"

static void playButtonClick(EnginePtr engine, std::shared_ptr<Entity> entity) {
    auto sceneHolder = engine->getModule<SceneHolder>();
    auto sc = sceneHolder->getValue(Scenes::GAME);
    engine->setScene(sc);
}

std::shared_ptr<Scene> mainMenu(EnginePtr engine)
{
    auto sc = engine->createScene<Scene>();
    auto lib = engine->getModule<IGraphicLib>();

    auto height = lib->getWindow().getHeight();
    auto width = lib->getWindow().getWidth();

    auto title = sc->createEntity();
    auto titlePos = title->addComponent<PositionComponent>((width / 2) - (700 / 2), (height / 3) - (122 / 2));
    title->addComponent<FixTextureComponent>()->setTextureId(Textures::TITLE);


    auto button = sc->createEntity();

    button->addComponent<EntityTypeComponent2>("button");
    button->addComponent<FixTextureComponent>()->setTextureId(Textures::PLAY_BUTTON);

    auto pos = button->addComponent<PositionComponent>((width / 2) - (200 / 2), (int) (height * 0.7) - (100 / 2));

    const Texture& buttonTexture = lib->getTextures()->getValue(Textures::PLAY_BUTTON);
    auto hitboxComponent = button->addComponent<HitboxComponent>(buttonTexture->getWidth(), buttonTexture->getHeight());

    auto buttonComponent = button->addComponent<ButtonComponent>();
    buttonComponent->setHitbox(Hitbox(pos, hitboxComponent));
    buttonComponent->setOnClick(playButtonClick);

    //auto optionButton = createButton(engine,sc,"img_3.png",width/2-(400/2),height*0.65-(100/2));
    //auto quitButton = createButton(engine,sc,"img.png",width/2-(400/2),height*0.85-(100/2));

    return sc;
}