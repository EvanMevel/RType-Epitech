//
// Created by aaama on 21/02/2023.
//

#ifndef R_TYPE_CLIENT_CREATETEXTBOX_H
#define R_TYPE_CLIENT_CREATETEXTBOX_H


#include <memory>
#include "Engine/Graphic/IGraphicLib.h"
#include "Engine/Entity.h"
#include "Engine/Scene.h"

std::shared_ptr<Entity> createTextBox(const std::shared_ptr<IGraphicLib> &lib, const std::shared_ptr<Scene> &sc, int x, int y);


#endif //R_TYPE_CLIENT_CREATETEXTBOX_H
