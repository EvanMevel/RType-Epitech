//
// Created by aaama on 17/01/2023.
//

#include "Engine.h"

Engine::Engine() : current(nullptr), _graphicLib(nullptr) {

}

Engine::~Engine() {
}

void Engine::setScene(std::shared_ptr<Scene> &sc) {
    this->current = sc;
}

std::shared_ptr<Scene> &Engine::getScene() {
    return this->current;
}

void Engine::setGraphicLib(std::shared_ptr<IGraphicLib> &graphicLib) {
    _graphicLib = graphicLib;
}

std::shared_ptr<IGraphicLib> &Engine::getGraphicLib() {
    return _graphicLib;
}

void Engine::updateScene() {
    currentTick++;
    if (current != nullptr)
        current->update(*this);
}

void Engine::updateGraphicLib() {
    if (_graphicLib != nullptr)
        _graphicLib->update(*this);
}

unsigned long long int Engine::getCurrentTick() const {
    return currentTick;
}

void Engine::setCurrentTick(unsigned long long int currentTick) {
    Engine::currentTick = currentTick;
}
