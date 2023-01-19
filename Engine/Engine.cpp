//
// Created by aaama on 17/01/2023.
//

#include "Engine.h"

void Engine::registerScene(Scene &sc) {
    this->scenes.push_back(sc);
}

void Engine::setScene(Scene &sc) {
    this->scene = sc;
}

Scene &Engine::getScene() const {
    return this->scene;
}

Engine::Engine(Scene &scene) : scene(scene) {
    registerScene(scene);
}

Entity Engine::createEntity() {
    return Entity(nextId++);
}
