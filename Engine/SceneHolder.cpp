//
// Created by audre on 02/02/2023.
//

#include "SceneHolder.h"

void SceneHolder::addScene(int index, std::shared_ptr<Scene> scene) {
    scenes[index] = scene;
}

std::shared_ptr<Scene> SceneHolder::getScene(int index) {
    return scenes[index];
}

