//
// Created by aaama on 24/01/2023.
//

#ifndef R_TYPE_SERVER_CREATEBUTTON_H
#define R_TYPE_SERVER_CREATEBUTTON_H

#include <string>
#include "Engine/Entity.h"
#include "Engine/Engine.h"
#include "Engine/Component/PositionComponent.h"
#include "Engine/Component/EntityTypeComponent.h"
#include "FixTextureComponent.h"

std::shared_ptr<Entity> createButton(Engine &e, std::shared_ptr<Scene> sc, const std::string &texturePath, int x, int y);

#endif //R_TYPE_SERVER_CREATEBUTTON_H
