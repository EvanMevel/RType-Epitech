//
// Created by aaama on 02/02/2023.
//

#include "MouseSystem.h"
#include "Engine/Engine.h"

void MouseSystem::update(EnginePtr engine) {
    auto lib = engine->getModule<IGraphicLib>();
    if (lib == nullptr)
        return;
    if(engine->getScene() == nullptr)
        return;
    if (lib->getMouse().isClicked(MouseCode::MOUSE_BUTTON_LEFT)){
        auto testMousePos = lib->getMouse().getPos();
        std::cout <<"pos x : " <<testMousePos.x << std::endl;
        std::cout <<"pos y : " <<testMousePos.y << std::endl;
    }

}
