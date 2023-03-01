//
// Created by aaama on 28/02/2023.
//

#include "Engine/Graphic/IGraphicLib.h"
#include "Engine/Scene.h"
#include "Textures.h"
#include "FixTextureComponent.h"
#include "Engine/Component/PositionComponent.h"

#ifndef R_TYPE_CLIENT_CREATEFIXTEXTURE_H
#define R_TYPE_CLIENT_CREATEFIXTEXTURE_H


std::shared_ptr<Entity> createFixTexture(const std::shared_ptr<Scene> &sc, Textures texture, int posx,int posy);

#endif //R_TYPE_CLIENT_CREATEFIXTEXTURE_H
