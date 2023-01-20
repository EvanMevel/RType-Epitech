//
// Created by aaama on 17/01/2023.
//

#include "Engine.h"

Engine::Engine() : _scene(nullptr), _graphicLib(nullptr) {

}

Engine::~Engine() {
    for (const auto &scene: scenes) {
        delete scene;
    }
    delete _graphicLib;
}

Scene *Engine::createScene() {
    auto *scene = new Scene(entityManager);
    scenes.push_back(scene);
    return scene;
}

void Engine::setScene(Scene *sc) {
    this->_scene = sc;
}

Scene *Engine::getScene() const {
    return this->_scene;
}

void Engine::setGraphicLib(IGraphicLib *graphicLib) {
    _graphicLib = graphicLib;
}

IGraphicLib *Engine::getGraphicLib() const {
    return _graphicLib;
}

void Engine::updateScene() {
    if (_scene != nullptr)
        _scene->update(*this);
}

void Engine::updateGraphicLib() {
    if (_graphicLib != nullptr)
        _graphicLib->update(*this);
}
