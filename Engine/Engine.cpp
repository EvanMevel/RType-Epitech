//
// Created by aaama on 17/01/2023.
//

#include "Engine.h"

Engine::Engine() : current(nullptr) {

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
    currentTick++;
    if (current != nullptr)
        current->update(*this);
}

unsigned long long int Engine::getCurrentTick() const {
    return currentTick;
}

void Engine::setCurrentTick(unsigned long long int currentTick) {
    Engine::currentTick = currentTick;
}
