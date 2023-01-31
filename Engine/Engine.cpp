//
// Created by aaama on 17/01/2023.
//

#include "Engine.h"

Engine::Engine() : current(nullptr) {

}

Engine::Engine(size_t startId) : entityManager(startId), current(nullptr) {

}

Engine::~Engine() {
}

void Engine::setScene(std::shared_ptr<Scene> &sc) {
    this->current = sc;
}

std::shared_ptr<Scene> &Engine::getScene() {
    return this->current;
}

void Engine::updateScene() {
    if (current != nullptr)
        current->update(*this);
}